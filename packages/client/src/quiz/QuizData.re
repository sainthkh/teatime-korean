type source = {
  url: string,
  name: string,
};

type multipleChoice = {
  question: string,
  answer: int,
  choices: array(string),
  explanation: string,
  sources: array(source),
};

type quiz = 
  | MultipleChoice(multipleChoice)
  ;

type deck = {
  quizzes: array(quiz),
};
