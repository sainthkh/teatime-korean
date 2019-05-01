[@react.component]
let make = () => {
  <div className="quiz-wrap">
    <div className="question">
      {ReasonReact.string("What is more polite ending?")}
    </div>
    <div className="choices">
      <button className="choice">{ReasonReact.string({j|-요|j})}</button>
      <button className="choice">{ReasonReact.string({j|-ㅂ니다|j})}</button>
    </div>
  </div>
};