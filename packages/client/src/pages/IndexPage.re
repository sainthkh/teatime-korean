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
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: {j|What's the best sentence for the blank?\nA: 내일도 올 거죠? \nB: 네. 그런데요. ____________|j},
      answer: 2,
      choices: [|
        {j|늦지 마세요.|j},
        {j|늦지 않았는데요.|j},
        {j|늦을 수도 있어요.|j},
        {j|늦어요.|j},
      |],
      explanation: {j|A asked if you can come tomorrow. Then, B answered yes, but wants to say he might be late. So, the best answer is "늦을 수도 있어요."|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: "You noticed that construction is going on near your school. How do you say this in Korean?",
      answer: 0,
      choices: [|
        {j|공사하네요.|j},
        {j|공사할게요.|j},
        {j|공사하죠.|j},
        {j|공사하는데요.|j},
      |],
      explanation: {j|-네요 is used when you noticed something new. So, the answer is 공사하네요.|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: "You bought your friend a pizza. You want to know if it tastes good. How should you ask?",
      answer: 1,
      choices: [|
        {j|맛있죠?|j},
        {j|맛있지?|j},
        {j|먹었지?|j},
        {j|맛있네요.|j},
      |],
      explanation: {j|When you ask for confirmation, you should end your sentence with -지/-죠. In this case, you're asking your friend. So, -지 is the better choice.|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: {j|What's NOT the good answer for this question?\n오늘 토요일이죠?|j},
      answer: 3,
      choices: [|
        {j|아니요. 오늘 일요일이죠.|j},
        {j|글쎄요. 잘 모르겠어요.|j},
        {j|네. 토요일이죠.|j},
        {j|토요일에 갔는데요.|j},
      |],
      explanation: {j|When you're asked if it's Saturday today, you need to answer about that. "토요일에 갔는데요" means "I went there Saturday."|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: "In Korean, where usually are the important things in the sentences?",
      answer: 1,
      choices: [|
        {j|In the front|j},
        {j|In the back|j},
      |],
      explanation: {j|Unlike English, important things are (tense, negativeness, etc.) in the front.|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: {j|You want to talk about your visit to 홍대. How should you start your talk?|j},
      answer: 1,
      choices: [|
        {j|홍대에 갔네요.|j},
        {j|홍대에 갔는데요.|j},
        {j|홍대에 가세요.|j},
        {j|홍대에 갔지요.|j},
      |],
      explanation: {j|-데요 is used when you want to invite someone to talk to you.|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
    MultipleChoice({
      question: {j|What's the best expression for the blank?\n 내일 치과에 가야해서, __________________.|j},
      answer: 3,
      choices: [|
        {j|늦는데요.|j},
        {j|늦죠.|j},
        {j|늦을래요.|j},
        {j|늦을 것 같아요.|j},
      |],
      explanation: {j|You want to talk about your opinion. So, 늦을 것 같아요 is the best choice.|j},
      sources: [|
        { 
          url: "https://www.youtube.com/watch?v=r4TNuJYeJM8",
          name: "Common Sentence Endings In Korean",
        }
      |],
    }),
  |],
};

[@react.component]
let make = () => {
  <>
    <div className="index-header">
      <div className="message">
        <h1>{ReasonReact.string("Quiz Korean")}</h1>
        <h2>{ReasonReact.string("Solve Korean language quizzes. Never forget what you have learned.")}</h2>
      </div>
      <Deck deck />
    </div>
    <div className="index-bottom">
      <h2>{ReasonReact.string("Wanna learn Korean with more quizzes?")}</h2>
      <div className="join-button-wrap">
        <NavButton href="/register" className="btn">{ReasonReact.string("Join the waitlist")}</NavButton>
      </div>
    </div>
  </>
};
