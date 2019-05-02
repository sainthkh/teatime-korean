[@react.component]
let make = (
  ~quiz: QuizData.quiz,
  ~answer,
  ~showAnswer
) => 
  switch(quiz) {
  | QuizData.MultipleChoice(d) => <MultipleChoice data=d answer showAnswer />
  }