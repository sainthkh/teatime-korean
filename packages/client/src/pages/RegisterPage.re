type state = {
  email: string,
  password: string,
  shouldNotBeEmpty: bool,
  duplicateEmail: bool,
  invalidEmail: bool,
  weakPassword: bool,
  waitForSignup: bool,
  errorsShouldBeFixed: bool,
};

type action = 
  | UpdateEmail(string)
  | EmptyEmailField(bool)
  | DuplicateEmail(bool)
  | UpdatePassword(string)
  | WaitForSignup
  | ServerError(array(EnumTypes.signupError))
  | ErrorsShouldBeFixed
  ;

let duplicateEmail = ReasonQL.gql({|
query CheckDuplicate($email: String!) {
  duplicateEmail(email: $email)
}
|});

module CheckDuplicate = ReasonQL.MakeRequest(CheckDuplicate, {
  let url = Config.graphqlUrl();
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
  let url = Config.graphqlUrl();
});

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action: action) => {
    switch(action) {
    | UpdateEmail(email) => { ...state, email: email, }
    | EmptyEmailField(err) => { ...state, shouldNotBeEmpty: err, }
    | UpdatePassword(password) => { 
      ...state, 
      password: password, 
      weakPassword: String.length(state.password) < 8,
    }
    | DuplicateEmail(duplicate) => { ...state, duplicateEmail: duplicate, }
    | WaitForSignup => { ...state, waitForSignup: true, }
    | ServerError(errors) => {
      ...state,
      shouldNotBeEmpty: String.length(state.email) == 0,
      weakPassword: String.length(state.password) < 8,
      duplicateEmail: Array.to_list(errors) |> List.exists(a => a == EnumTypes.DuplicateEmail),
      invalidEmail: Array.to_list(errors) |> List.exists(a => a == EnumTypes.InvalidEmail),
      waitForSignup: false,
      errorsShouldBeFixed: false,
    }
    | ErrorsShouldBeFixed => { ...state, errorsShouldBeFixed: true }
    }
  }, {
    email: "",
    password: "",
    shouldNotBeEmpty: false,
    weakPassword: false,
    duplicateEmail: false,
    invalidEmail: false,
    waitForSignup: false,
    errorsShouldBeFixed: false,
  });

  let checkDuplicateEmail = () => {
    CheckDuplicate.send({ email: state.email })
    ->CheckDuplicate.finished(data => {
      dispatch(DuplicateEmail(data.duplicateEmail))
    });
  };

  <div className="register-page">
    <form 
      className="register-form" 
      method="POST" 
      onSubmit={event => {
        event->ReactEvent.Synthetic.preventDefault;
        if(!state.shouldNotBeEmpty && !state.weakPassword && !state.duplicateEmail) {
          dispatch(WaitForSignup)
          Signup.send({ email: state.email, password: state.password })
          ->Signup.finished(data => {
            switch(Array.length(data.signup.errors)) {
            | 0 => ReasonReactRouter.push("/thankyou")
            | _ => dispatch(ServerError(data.signup.errors))
            }
          })
        } else {
          dispatch(ErrorsShouldBeFixed);
        }
      }}
    >
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
          state.invalidEmail 
          ? <div className="form-error">{ReasonReact.string("is invalid.")}</div>
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
          if (state.duplicateEmail) {
            checkDuplicateEmail();
          }
        }}
        onBlur={_ => {
          switch(String.length(state.email)) {
          | 0 => dispatch(EmptyEmailField(true))
          | _ => {
            dispatch(EmptyEmailField(false));
            checkDuplicateEmail();
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
      />
      {
        state.waitForSignup
        ? <div>{ReasonReact.string("Please wait.")}</div>
        : <>
            <button>
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