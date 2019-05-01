[@react.component]
let make = (~quiz: QuizData.quiz) => 
  switch(quiz) {
  | QuizData.MultipleChoice(d) => <MultipleChoice data=d />
  }