[%%raw {|require("./styles.scss")|}]

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let page = () => {
    switch(url.path) {
    | [] | [""] | ["/"] => <IndexPage />
    | ["register"] => <RegisterPage />
    | ["thankyou"] => <ThankyouPage />
    | _ => <IndexPage />
    };
  };

  <>
    { page(); }
  </>;
}
