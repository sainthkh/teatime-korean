[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let page = () => {
    switch(url.path) {
    | [] | [""] | ["/"] => <IndexPage />
    | ["thankyou"] => <ThankyouPage />
    | _ => <Error404Page />
    };
  };

  <>
    { page(); }
  </>;
}
