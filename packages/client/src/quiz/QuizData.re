type multipleChoice = {
  question: string,
  answer: int,
  choices: array(string),
  explanation: string,
};

type quiz = 
  | MultipleChoice(multipleChoice)
  ;

type deck = {
  quizzes: array(quiz),
};
