[@react.component]
let make = (~text) => {
  <div className="question">
    {
      text 
      |> Js.String.split("\n") 
      |> Array.mapi((i, line) => {
        <span key=string_of_int(i)>
          {ReasonReact.string({j|$line|j})}<br/>
        </span>
      })
      |> ReasonReact.array
    }
  </div>
};