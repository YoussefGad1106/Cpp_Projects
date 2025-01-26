#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionsLevels { Easy = 1, Medium = 2, Hard = 3, Mix_Levels = 4 };
enum enOperatorsTypes { Add = 1, Subtract = 2, Multiply = 3, Divide = 4, Mix_Operators = 5 };

struct strMathGame
{
    short numberOfQuestions = 0, levelOfQuestions, operatorChoice, numberOfRightAnswers = 0, numberOfWrongAnswers = 0;
    char questionOperator;
    int questionAnswer = 0, userAnswer = 0, firstOperand = 0, secondOperand = 0;
    string restartChoice;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

void QuestionsLevel(strMathGame& mathGame)
{

    cout << "\nPlease choose the level of the questions [1]- Easy [2]- Medium [3]- Hard [4]- Mix: ";
    cin >> mathGame.levelOfQuestions;
}

enQuestionsLevels ChosenQuestionLevel(strMathGame mathGame)
{
    if (mathGame.levelOfQuestions == 4)
    {
        return (enQuestionsLevels)RandomNumber(1, 3);
    }
    else
    {
        return (enQuestionsLevels)mathGame.levelOfQuestions;
    }
}

int QuestionOperands(enQuestionsLevels level) {
    switch (level)
    {
    case Easy: return RandomNumber(1, 9);
    case Medium: return RandomNumber(10, 99);
    case Hard: return RandomNumber(100, 999);
    default: return 0;
    }
}

void QuestionOperator(strMathGame& mathGame)
{
    cout << "Please choose an operator [1]: + [2]: - [3]: * [4]: / [5]: Mix  :  ";
    cin >> mathGame.operatorChoice;
}

enOperatorsTypes ChosenOperator(strMathGame mathGame)
{
    if (mathGame.operatorChoice == 5)
    {
        return (enOperatorsTypes)RandomNumber(1, 4);
    }
    else
    {
        return (enOperatorsTypes)mathGame.operatorChoice;
    }
}

char GetOperatorSymbol(enOperatorsTypes operatorChoice)
{
    switch (operatorChoice)
    {
    case Add: return '+';
    case Subtract: return '-';
    case Multiply: return '*';
    case Divide: return '/';
    default: return '?';
    }
}

void GenerateQuestionOperands(strMathGame& mathGame)
{
    mathGame.firstOperand = QuestionOperands(ChosenQuestionLevel(mathGame));
    mathGame.secondOperand = QuestionOperands(ChosenQuestionLevel(mathGame));
}

void GenerateQuestionOperator(strMathGame& mathGame)
{
    mathGame.questionOperator = GetOperatorSymbol(ChosenOperator(mathGame));
}

void GenerateQuestion(strMathGame& mathGame, short questionNumber)
{
    GenerateQuestionOperands(mathGame);
    GenerateQuestionOperator(mathGame);

    cout << "\nQuestion " << questionNumber << ":\n";
    cout << mathGame.firstOperand << " \n" << mathGame.secondOperand << " " << mathGame.questionOperator << "\n";
    cout << "----------------------------------\n";
}

int CalculateAnswer(strMathGame& mathGame)
{
    switch (mathGame.questionOperator)
    {
        case '+': mathGame.questionAnswer = mathGame.firstOperand + mathGame.secondOperand; break;
        case '-': mathGame.questionAnswer = mathGame.firstOperand - mathGame.secondOperand; break;
        case '*': mathGame.questionAnswer = mathGame.firstOperand * mathGame.secondOperand; break;
        case '/': mathGame.questionAnswer = mathGame.firstOperand / mathGame.secondOperand; break;
    }

    return mathGame.questionAnswer;
}

int UserAnswer(strMathGame& mathGame)
{
    cin >> mathGame.userAnswer;

    return mathGame.userAnswer;
}

bool CompareAnswer(strMathGame mathGame)
{
    return UserAnswer(mathGame) == CalculateAnswer(mathGame);
}

void CheckAnswer(strMathGame& mathGame)
{
    if (CompareAnswer(mathGame))
    {
        system("Color 2F");
        mathGame.numberOfRightAnswers++;
    }
    else
    {
        system("Color 4F");
        cout << "\aWrong! The correct answer is: " << CalculateAnswer(mathGame) << "\n";
        mathGame.numberOfWrongAnswers++;
    }
}

string CheckPassStatus(strMathGame& mathGame)
{
    if (mathGame.numberOfRightAnswers > mathGame.numberOfWrongAnswers)
        return "Pass";
    else
        return "Fail";
}

void DisplayFinalResults(strMathGame mathGame) 
{
    system("Color 6F");
    cout << "\n----------------------------------------------------------------------------\n";
    cout << "Final Result: " << CheckPassStatus(mathGame) << endl;
    cout << "Questions Level: " << mathGame.levelOfQuestions << endl;
    cout << "Operator Type: " << mathGame.questionOperator << endl;
    cout << "Number of Right Answers: " << mathGame.numberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << mathGame.numberOfWrongAnswers << endl;
    cout << "----------------------------------------------------------------------------\n";
}

void MathGame(strMathGame& mathGame)
{
    do {
        system("cls");
        system("Color 0F");

        cout << "How many questions do you want? ";
        cin >> mathGame.numberOfQuestions;

        QuestionsLevel(mathGame);
        QuestionOperator(mathGame);

        for (int i = 0; i < mathGame.numberOfQuestions; i++) 
        {

            GenerateQuestionOperator(mathGame);
            GenerateQuestion(mathGame, i + 1);
            CheckAnswer(mathGame);
        }

        cout << "Do you want to play again (Y/N)? ";
        cin >> mathGame.restartChoice;

    } while (mathGame.restartChoice == "Y" || mathGame.restartChoice == "y");

    DisplayFinalResults(mathGame);
}

int main()
{
    srand((unsigned)time(NULL));

    strMathGame mathGame;

    MathGame(mathGame);

}