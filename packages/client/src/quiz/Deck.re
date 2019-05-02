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
    | Next => { current: state.current + 1, answered: false }
    | Answered => { ...state, answered: true }
    },
    {current: 0, answered: false}
  );

  <div className="quiz-wrap">
    {switch(state.current < Array.length(deck.quizzes)) {
    | true => <Quiz quiz=deck.quizzes[state.current] answer={() => dispatch(Answered)}/>
    | false => {
      <div className="join-waitlist">
        <h3>{ReasonReact.string("Did you like it? Do you want more?")}</h3>
        <p className="subhead">{ReasonReact.string("If so, please join the waitlist.")}</p>
        <button className="btn">{ReasonReact.string("Let me in")}</button>
        <p className="warning">{ReasonReact.string("NOTE: I'm currently validating this idea. If there is not enough people in waitlist, I might not continue this project.")}</p>
      </div>
    }
    }}
    
    {
      state.answered
      ? <div className="next-btn-wrap">
          <button className="next-btn" onClick={_ => dispatch(Next)}>{ReasonReact.string("Next")}</button>
        </div>
      : ReasonReact.null
    }
  </div>
};