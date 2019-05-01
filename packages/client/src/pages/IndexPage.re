let deck: QuizData.deck = {
  quizzes: [|
    MultipleChoice({
      question: "Which ending is more polite?",
      answer: 2,
      choices: [|
        {j|-요|j},
        {j|-ㅂ니다|j},
      |],
    })
  |],
};

[@react.component]
let make = () => {
  <>
    <div className="index-header">
      <div className="message">
        <h1>{ReasonReact.string("Teatime Korean")}</h1>
        <h2>{ReasonReact.string("You won't forget Korean language you learned.")}</h2>
      </div>
      <Deck deck />
    </div>
    <div className="index-bottom">
      <h2>{ReasonReact.string("Wanna learn Korean with more quizzes?")}</h2>
      <div className="join-button-wrap">
        <button className="btn">{ReasonReact.string("Join the waitlist")}</button>
      </div>
    </div>
  </>
};
