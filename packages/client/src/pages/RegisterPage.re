[@react.component]
let make = () => {
  <div className="register-page">
    <form className="register-form" method="POST">
      <h1>{ReasonReact.string("Join the Waitlist")}</h1>
      <p>{ReasonReact.string("I'll send you a notice when the site opens.")}</p>
      <label htmlFor="sign-up-form-email">{ReasonReact.string("email")}</label>
      <input type_="email" id="sign-up-form-email" />
      <label htmlFor="sign-up-form-password">{ReasonReact.string("password")}</label>
      <input type_="password" id="sign-up-form-password" />
      <button>{ReasonReact.string("Let me in")}</button>
    </form>
  </div>
};