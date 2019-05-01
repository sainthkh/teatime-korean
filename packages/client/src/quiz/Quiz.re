[@react.component]
let make = (
  ~quiz: QuizData.quiz,
  ~answer
) => 
  switch(quiz) {
  | QuizData.MultipleChoice(d) => <MultipleChoice data=d answer />
  }