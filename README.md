                  ┌───────────────────┐
                  │       Exam        │  ← Abstract Base Class
                  ├───────────────────┤
                  │ - examID : string │
                  │ - subject : string│
                  │ - duration : int  │
                  ├───────────────────┤
                  │ + displayExamInfo()│
                  │ + gradeExam() = 0 │  ← Pure Virtual
                  └─────────┬─────────┘
                            │
            ┌───────────────┴───────────────┐
            │                               │
┌─────────────────────────┐       ┌─────────────────────────┐
│ MultipleChoiceExam       │       │ EssayExam               │
├─────────────────────────┤       ├─────────────────────────┤
│ - numQuestions : int     │       │ - topic : string        │
│ - correctAnswers : int*  │       │ - maxWords : int        │
│ - studentAnswers : int*  │       │ - essayContent : string*│
│ - pointsPerQuestion :double│     │ - rubricScores : double*│
├─────────────────────────┤       │ - numCriteria : int     │
│ + setCorrectAnswer()     │       ├─────────────────────────┤
│ + setStudentAnswer()     │       │ + setEssayContent()     │
│ + gradeExam() override   │       │ + setRubricScore()      │
└─────────────────────────┘       │ + gradeExam() override  │
                                  └─────────────────────────┘
