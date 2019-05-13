[@bs.val] external nodeEnv: string = "process.env.NODE_ENV";

let graphqlUrl = () => {
  switch(nodeEnv) {
  | "production" => "https://quizkorean.com/graphql"
  | _ => "http://localhost:8080/graphql"
  }
};