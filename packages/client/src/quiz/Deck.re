type state = {
  current: int,
  answered: bool,
};

type action = 
  | Next
  | Answered
  ;

[@react.component]
let make = (~deck: QuizData.deck) => {
  let (state, dispatch) = React.useReducer((state, action) => 
    switch(action) {
    | Next => { ...state, current: state.current + 1 }
    | Answered => { ...state, answered: true }
    },
    {current: 0, answered: false}
  );

  <div className="quiz-wrap">
    <Quiz quiz=deck.quizzes[0] answer={() => dispatch(Answered)}/>
    {
      state.answered
      ? <div><button>{ReasonReact.string("Next")}</button></div>
      : ReasonReact.null
    }
  </div>
};