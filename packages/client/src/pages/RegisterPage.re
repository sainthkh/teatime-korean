type state = {
  email: string,
  password: string,
  shouldNotBeEmpty: bool,
  duplicateEmail: bool,
  weakPassword: bool,
  waitForSignup: bool,
  errorsShouldBeFixed: bool,
  thankyou: bool,
};

type action = 
  | UpdateEmail(string)
  | EmptyEmailField(bool)
  | DuplicateEmail(bool)
  | UpdatePassword(string)
  | WeakPassword(bool)
  | WaitForSignup
  | Finished
  | ServerError(array(EnumTypes.signupError))
  | ErrorsShouldBeFixed
  ;

let duplicateEmail = ReasonQL.gql({|
query CheckDuplicate($email: String!) {
  duplicateEmail(email: $email)
}
|});

module CheckDuplicate = ReasonQL.MakeRequest(CheckDuplicate, {
  let url = "http://localhost:8080/graphql";
});


let signup = ReasonQL.gql({|
mutation SignupMutation($email: String!, $password: String!) {
  signup(email: $email, password: $password) {
    success
    errors
  }
}
|});

module Signup = ReasonQL.MakeRequest(SignupMutation, {
  let url = "http://localhost:8080/graphql";
});

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action: action) => {
    switch(action) {
    | UpdateEmail(email) => { ...state, email: email, }
    | EmptyEmailField(err) => { ...state, shouldNotBeEmpty: err, }
    | UpdatePassword(password) => { ...state, password: password, }
    | WeakPassword(err) => { ...state, weakPassword: err, }
    | DuplicateEmail(duplicate) => { ...state, duplicateEmail: duplicate, }
    | WaitForSignup => { ...state, waitForSignup: true, }
    | ServerError(errors) => {
      ...state,
      shouldNotBeEmpty: String.length(state.email) == 0,
      weakPassword: String.length(state.password) < 8,
      duplicateEmail: Array.to_list(errors) |> List.exists(a => a == EnumTypes.DuplicateEmail),
      waitForSignup: false,
      errorsShouldBeFixed: false,
    }
    | Finished => { ...state, thankyou: true }
    | ErrorsShouldBeFixed => { ...state, errorsShouldBeFixed: true }
    }
  }, {
    email: "",
    password: "",
    shouldNotBeEmpty: false,
    weakPassword: false,
    duplicateEmail: false,
    waitForSignup: false,
    errorsShouldBeFixed: false,
    thankyou: false,
  });

  <div className="register-page">
    <form className="register-form" method="POST">
      <h1>{ReasonReact.string("Join the Waitlist")}</h1>
      <p>{ReasonReact.string("I'll send you a notice when the site opens.")}</p>
      <div className="label-wrap">
        <label htmlFor="sign-up-form-email">{ReasonReact.string("email")}</label>
        { 
          state.duplicateEmail 
          ? <div className="form-error">{ReasonReact.string("is already taken.")}</div>
          : ReasonReact.null
        }
        {
          state.shouldNotBeEmpty
          ? <div className="form-error">{ReasonReact.string("shouldn't be empty.")}</div>
          : ReasonReact.null
        }
      </div>
      <input 
        type_="email" 
        id="sign-up-form-email" 
        value=state.email 
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;
          dispatch(UpdateEmail(value));
        }}
        onBlur={_ => {
          switch(String.length(state.email)) {
          | 0 => dispatch(EmptyEmailField(true))
          | _ => {
            dispatch(EmptyEmailField(false))
            CheckDuplicate.send({ email: state.email })
            ->CheckDuplicate.finished(data => {
              dispatch(DuplicateEmail(data.duplicateEmail))
            });
          }
          }
        }}
      />
      <div className="label-wrap">
        <label htmlFor="sign-up-form-password">{ReasonReact.string("password")}</label>
        {
          state.weakPassword
          ? <div className="form-error">{ReasonReact.string("must be at least 8 characters.")}</div>
          : ReasonReact.null
        }
      </div>
      <input 
        type_="password" 
        id="sign-up-form-password" 
        value=state.password 
        onChange={event => {
          let value = event->ReactEvent.Form.target##value;
          dispatch(UpdatePassword(value));
        }}
        onBlur={_ => dispatch(WeakPassword(String.length(state.password) < 8)) } 
      />
      {
        state.waitForSignup
        ? <div>{ReasonReact.string("Please wait.")}</div>
        : <>
            <button 
              onClick={event => {
                event->ReactEvent.Synthetic.preventDefault;
                if(!state.shouldNotBeEmpty && !state.weakPassword && !state.duplicateEmail) {
                  dispatch(WaitForSignup)
                  Signup.send({ email: state.email, password: state.password })
                  ->Signup.finished(data => {
                    switch(Array.length(data.signup.errors)) {
                    | 0 => dispatch(Finished)
                    | _ => dispatch(ServerError(data.signup.errors))
                    }
                  })
                } else {
                  dispatch(ErrorsShouldBeFixed);
                }
              }}
            >
              {ReasonReact.string("Let me in")}
            </button>
            {
              state.errorsShouldBeFixed 
              ? <div className="form-error">{ReasonReact.string("Errors should be fixed.")}</div>
              : ReasonReact.null
            }
          </>
      }
    </form>
  </div>
};