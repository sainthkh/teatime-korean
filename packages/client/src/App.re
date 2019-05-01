[%%raw {|require("./styles.scss")|}]

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  let page = () => {
    switch(url.path) {
    | [] | [""] | ["/"] => <IndexPage />
    | _ => <IndexPage />
    };
  };

  <>
    { page(); }
  </>;
}
