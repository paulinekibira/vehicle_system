#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Exam {
protected:
    string examID;
    string subject;
    int duration;

public:
    Exam(string id, string sub, int dur) : examID(id), subject(sub), duration(dur) {}

    virtual ~Exam() {}

    virtual double gradeExam() = 0;

    void displayExamInfo() {
        cout << "Exam ID: " << examID << ", Subject: " << subject << ", Duration: " << duration << " mins";
    }
};

class MultipleChoiceExam : public Exam {
private:
    int numQuestions;
    int* correctAnswers;
    int* studentAnswers;
    double pointsPerQuestion;

public:
    MultipleChoiceExam(string id, string sub, int dur, int questions, double points)
        : Exam(id, sub, dur), numQuestions(questions), pointsPerQuestion(points) {

        if (questions <= 0) {
            throw invalid_argument("Number of questions must be positive");
        }
        if (points <= 0) {
            throw invalid_argument("Points per question must be positive");
        }

        correctAnswers = new int[questions];
        studentAnswers = new int[questions];

        for (int i = 0; i < questions; i++) {
            correctAnswers[i] = 0;
            studentAnswers[i] = 0;
        }
    }

    ~MultipleChoiceExam() {
        delete[] correctAnswers;
        delete[] studentAnswers;
    }

    void setCorrectAnswer(int questionNum, int answer) {
        if (questionNum < 0 || questionNum >= numQuestions) {
            throw out_of_range("Invalid question number");
        }
        correctAnswers[questionNum] = answer;
    }

    void setStudentAnswer(int questionNum, int answer) {
        if (questionNum < 0 || questionNum >= numQuestions) {
            throw out_of_range("Invalid question number");
        }
        studentAnswers[questionNum] = answer;
    }

    double gradeExam() override {
        int correct = 0;
        for (int i = 0; i < numQuestions; i++) {
            if (studentAnswers[i] == correctAnswers[i]) {
                correct++;
            }
        }
        return correct * pointsPerQuestion;
    }
};

class EssayExam : public Exam {
private:
    string topic;
    int maxWords;
    string* essayContent;
    double* rubricScores;
    int numCriteria;

public:
    EssayExam(string id, string sub, int dur, string t, int maxW, int criteria)
        : Exam(id, sub, dur), topic(t), maxWords(maxW), numCriteria(criteria) {

        if (maxW <= 0) {
            throw invalid_argument("Max words must be positive");
        }
        if (criteria <= 0) {
            throw invalid_argument("Number of criteria must be positive");
        }

        essayContent = new string;
        rubricScores = new double[criteria];

        for (int i = 0; i < criteria; i++) {
            rubricScores[i] = 0.0;
        }
    }

    ~EssayExam() {
        delete essayContent;
        delete[] rubricScores;
    }

    void setEssayContent(const string& content) {
        if (content.length() > static_cast<size_t>(maxWords)) {
            throw length_error("Essay exceeds maximum word count");
        }
        *essayContent = content;
    }

    void setRubricScore(int criterion, double score) {
        if (criterion < 0 || criterion >= numCriteria) {
            throw out_of_range("Invalid criterion number");
        }
        if (score < 0 || score > 100) {
            throw invalid_argument("Score must be between 0 and 100");
        }
        rubricScores[criterion] = score;
    }

    double gradeExam() override {
        double total = 0;
        for (int i = 0; i < numCriteria; i++) {
            total += rubricScores[i];
        }
        return total / numCriteria;
    }
};

int main() {
    cout << "----- ONLINE EXAM SYSTEM -----\n" << endl;

    try {
        MultipleChoiceExam mcExam("MC001", "Mathematics", 60, 5, 20.0);
        mcExam.displayExamInfo();
        cout << endl;

        mcExam.setCorrectAnswer(0, 2);
        mcExam.setCorrectAnswer(1, 1);
        mcExam.setCorrectAnswer(2, 3);
        mcExam.setCorrectAnswer(3, 4);
        mcExam.setCorrectAnswer(4, 2);

        mcExam.setStudentAnswer(0, 2);
        mcExam.setStudentAnswer(1, 1);
        mcExam.setStudentAnswer(2, 3);
        mcExam.setStudentAnswer(3, 2);
        mcExam.setStudentAnswer(4, 2);

        cout << "MC Exam Score: " << mcExam.gradeExam() << "/100\n" << endl;

        EssayExam essayExam("ESS001", "English", 120, "Climate Change", 1000, 3);
        essayExam.displayExamInfo();
        cout << endl;

        essayExam.setEssayContent("Climate change is a pressing global issue");
        essayExam.setRubricScore(0, 85);
        essayExam.setRubricScore(1, 90);
        essayExam.setRubricScore(2, 88);

        cout << "Essay Exam Score: " << essayExam.gradeExam() << endl;

    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
