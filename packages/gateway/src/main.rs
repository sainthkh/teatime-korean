use std::io;
use std::sync::Arc;

//#[macro_use]
extern crate juniper;
extern crate chrono;

use actix_web::middleware::cors::Cors;
use actix_web::{http, middleware, web, App, Error, HttpResponse, HttpServer};
use futures::future::Future;
use juniper::http::graphiql::graphiql_source;
use juniper::http::GraphQLRequest;

use juniper_from_schema::graphql_schema_from_file;

use mongodb::{Client as MongoClient, ThreadedClient, doc, bson};
use mongodb::db::ThreadedDatabase;
use sodiumoxide::crypto::pwhash;

use chrono::prelude::*;

// This is the important line
graphql_schema_from_file!("src/schema.gql");

pub struct Context {
    db: mongodb::db::Database,
}

impl Context {
    fn check_duplicate_email(&self, email: &String) -> bool {
        let user = 
            self.db.collection("users").find_one(Some(doc!{"_id": email}), None)
            .expect("Failed to load user");
        match user {
        | Some(_d) => true,
        | None => false,
        }
    }
}

impl juniper::Context for Context {}

pub struct Query;

impl QueryFields for Query {
    fn field_duplicate_email(
        &self,
        executor: &juniper::Executor<'_, Context>,
        email: String,
    ) -> juniper::FieldResult<bool> {
        Ok(executor.context().check_duplicate_email(&email))
    }
}

pub struct Mutation;

impl MutationFields for Mutation {
    fn field_signup(
        &self, 
        executor: &juniper::Executor<'_, Context>,
        _trail: &QueryTrail<'_, SignupResponse, Walked>,
        email: String,
        password: String,
    ) -> juniper::FieldResult<SignupResponse> {
        let context = executor.context();

        let mut errors = Vec::new();

        if context.check_duplicate_email(&email) {
            errors.push(SignupError::DuplicateEmail);
        }

        if password.len() < 8 {
            errors.push(SignupError::WeakPassword);
        }

        if errors.len() == 0 {
            let pwh = pwhash::pwhash(password.as_bytes(), 
                pwhash::OPSLIMIT_INTERACTIVE,
                pwhash::MEMLIMIT_INTERACTIVE
            ).unwrap();
            context.db.collection("users").insert_one(doc!{
                "_id": &email,
                "password": base64::encode(&pwh[..]),
                "signupDate": Utc::now().to_rfc3339(),
            }, None)
            .expect("Failed to save a new user data.");

            Ok(SignupResponse {
                success: true,
                errors: [].to_vec(),
            })
        } else {
            Ok(SignupResponse {
                success: false,
                errors,
            })
        }
    }
}

pub struct SignupResponse {
    success: bool,
    errors: Vec<SignupError>,
}

impl SignupResponseFields for SignupResponse {
    fn field_success(
        &self, 
        _executor: &juniper::Executor<'_, Context>
    ) -> juniper::FieldResult<&bool> {
        Ok(&self.success)
    }

    fn field_errors(
        &self, 
        _executor: &juniper::Executor<'_, Context>
    ) -> juniper::FieldResult<&Vec<SignupError>> {
        Ok(&self.errors)
    }
}

pub struct State {
    schema: std::sync::Arc<Schema>,
    context: Context,
}

fn graphiql() -> HttpResponse {
    let html = graphiql_source("http://localhost:8080/graphql");
    HttpResponse::Ok()
        .content_type("text/html; charset=utf-8")
        .body(html)
}

fn graphql(
    st: web::Data<Arc<State>>,
    data: web::Json<GraphQLRequest>,
) -> impl Future<Item = HttpResponse, Error = Error> {
    web::block(move || {
        let res = data.execute(&st.schema, &st.context);
        Ok::<_, serde_json::error::Error>(serde_json::to_string(&res)?)
    })
    .map_err(Error::from)
    .and_then(|user| {
        Ok(HttpResponse::Ok()
            .content_type("application/json")
            .body(user))
    })
}

fn main() -> io::Result<()> {
    std::env::set_var("RUST_LOG", "actix_web=info");
    env_logger::init();

    // Create Juniper schema
    let client = MongoClient::connect("localhost", 27017)
    .expect("Failed to initialize client.");

    let state = Arc::new(State {
        schema: Arc::new(Schema::new(Query, Mutation)),
        context: Context {
            db: client.db("ttmik"),
        },
    });

    // Start http server
    HttpServer::new(move || {
        App::new()
            .data(state.clone())
            .wrap(
                Cors::new()
                    // For development
                    .allowed_origin("http://localhost:8000") 
                    .allowed_origin("http://localhost:8080")
                    .allowed_methods(vec!["GET", "POST"])
                    .allowed_headers(vec![http::header::AUTHORIZATION, http::header::ACCEPT])
                    .allowed_header(http::header::CONTENT_TYPE)
                    .max_age(3600)
            )
            .wrap(middleware::Logger::default())
            .service(web::resource("/graphql").route(web::post().to_async(graphql)))
            .service(web::resource("/graphiql").route(web::get().to(graphiql)))
    })
    .bind("127.0.0.1:8080")?
    .run()
}
