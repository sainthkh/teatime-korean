type state = {
  clicked: int,
};

type action = 
  | Click(int)
  ;

[@react.component]
let make = (
  ~data: QuizData.multipleChoice,
  ~answer
) => {
  let (state, dispatch) = React.useReducer((_state, action) => {
    switch(action) {
    | Click(num) => { clicked: num }
    }
  }, {clicked: -1});
  let showAnswer = () => state.clicked != -1;

  <>
    <div className="question">
      {ReasonReact.string(data.question)}
    </div>
    <div className="choices">
      {data.choices |> Array.mapi((i, choice: string) => {
        switch(showAnswer()) {
        | false => {
          <button 
            key=string_of_int(i)
            className="choice" 
            onClick={_ => {
              answer()
              dispatch(Click(i))
            }}
          >
            {ReasonReact.string(choice)}
          </button>
        }
        | true => {
          let className = () => {
            switch(i == data.answer) {
            | true => "choice correct"
            | false => {
              switch(i == state.clicked) {
              | true => "choice wrong"
              | false => "choice gray"
              }
            }
            }
          };

          <div
            key=string_of_int(i)
            className=className()
          >
            {ReasonReact.string(choice)}
          </div>
        }
        }
      }) |> ReasonReact.array}
    </div>
    {
      showAnswer()
      ? {
        <div className="explanation">
          <div className="title">{ReasonReact.string({j|✏️ Explanation|j})}</div>
          <p>{ReasonReact.string(data.explanation)}</p>
        </div>
      }
      : ReasonReact.null
    }
  </>
};