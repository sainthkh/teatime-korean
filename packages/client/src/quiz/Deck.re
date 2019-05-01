type state = {
  current: int,
};

type action = 
  | Next
  ;

[@react.component]
let make = (~deck: QuizData.deck) => {
  <Quiz quiz=deck.quizzes[0] />
};