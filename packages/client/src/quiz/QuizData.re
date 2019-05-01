type multipleChoice = {
  question: string,
  answer: int,
  choices: array(string),
};

type quiz = 
  | MultipleChoice(multipleChoice)
  ;

type deck = {
  quizzes: array(quiz),
};
