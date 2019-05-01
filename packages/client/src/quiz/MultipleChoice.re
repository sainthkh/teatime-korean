[@react.component]
let make = (
  ~data: QuizData.multipleChoice,
  ~answer
) => {
  <>
    <div className="question">
      {ReasonReact.string(data.question)}
    </div>
    <div className="choices">
      {data.choices |> Array.mapi((i, choice: string) => {
        <button 
          key=string_of_int(i)
          className="choice" 
          onClick={_ => answer()}
        >
          {ReasonReact.string(choice)}
        </button>
      }) |> ReasonReact.array}
    </div>
  </>
};