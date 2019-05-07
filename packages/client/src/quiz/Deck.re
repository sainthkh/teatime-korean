type state = {
  current: int,
  showAnswer: bool,
};

type action = 
  | Next
  | Answered
  ;

[@react.component]
let make = (~deck: QuizData.deck) => {
  let (state, dispatch) = React.useReducer((state, action) => 
    switch(action) {
    | Next => { current: state.current + 1, showAnswer: false }
    | Answered => { ...state, showAnswer: true }
    },
    {current: 0, showAnswer: false}
  );

  <div className="quiz-wrap">
    {switch(state.current < Array.length(deck.quizzes)) {
    | true => 
      <Quiz 
        quiz=deck.quizzes[state.current] 
        answer={() => dispatch(Answered)}
        showAnswer=state.showAnswer
      />
    | false => {
      <div className="join-waitlist">
        <h3>{ReasonReact.string("Did you like it? Do you want more?")}</h3>
        <p className="subhead">{ReasonReact.string("If so, please join the waitlist.")}</p>
        <NavButton href="/register" className="btn">{ReasonReact.string("Let me in")}</NavButton>
      </div>
    }
    }}
    
    {
      state.showAnswer
      ? <div className="next-btn-wrap">
          <button className="next-btn" onClick={_ => dispatch(Next)}>{ReasonReact.string("Next")}</button>
        </div>
      : ReasonReact.null
    }
  </div>
};