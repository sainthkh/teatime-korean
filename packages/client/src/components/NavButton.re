[@react.component]
let make = (
  ~href,
  ~className="",
  ~children
) => {
  <button href className=className onClick={event => {
    ReasonReactRouter.push(href)
    event->ReactEvent.Synthetic.preventDefault
  }}>
    children
  </button>
}