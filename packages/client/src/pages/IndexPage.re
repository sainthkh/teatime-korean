let deck: QuizData.deck = {
  quizzes: [|
    MultipleChoice({
      question: "Which ending is more polite?",
      answer: 1,
      choices: [|
        {j|-요|j},
        {j|-ㅂ니다|j},
      |],
      explanation: {j|Use -ㅂ니다 when you want to be more polite.|j},
    })
  |],
};

[@react.component]
let make = () => {
  <>
    <div className="index-header">
      <div className="message">
        <h1>{ReasonReact.string("Teatime Korean")}</h1>
        <h2>{ReasonReact.string("Solve Korean language quizzes. Never forget what you learned.")}</h2>
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
