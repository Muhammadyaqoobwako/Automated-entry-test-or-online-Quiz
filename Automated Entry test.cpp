#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include<typeinfo>
#include <cstdlib>
#include<conio.h>
using namespace std;

class Question {
public:
    string question;
    string options[4];
    char correctAnswer;
};

class BankQuestions {
private:
    Question questions[20];

public:
    BankQuestions() {
        questions[0] = {"What does CPU stand for?", {"A. Central Processing Unit", "B. Computer Processing Unit", "C. Central Processor Unit", "D. Computer Processor Unit"}, 'A'};
        questions[1] = {"What does RAM stand for?", {"A. Random Only Memory", "B. Random Access Memory", "C. Read Only Memory", "D. Ready Organized Memory"}, 'B'};
        questions[2] = {"ALU stands for -------- ?", {"A. Arithmetic Longest Unit", "B. Arithmetic Logic Unit", "C. Arithmetic Longest United", "D. None of these"}, 'B'};
        questions[3] = {"The term ‘Computer’ is derived from__?", {"A. German", "B. Persian", "C. Latin", "D. None of these"}, 'C'};
        questions[4] = {"ALU and Control Unit jointly known as__?", {"A. RAM", "B. ROM", "C. CPU", "D. None of these"}, 'C'};
        questions[5] = {"Handheld computer is also called__?", {"A. Laptop computer", "B. Palmtop computer", "C. Notebook computer", "D. None of these"}, 'B'};
        questions[6] = {"Which number system is used by computer machines?", {"A. digital", "B. decimal", "C. analogue", "D. binary"}, 'D'};
        questions[7] = {"The main function of a web server is to store and process", {"A. internet", "B. websites", "C. database", "D. programs"}, 'B'};
        questions[8] = {"A computer program that translates one statement of program instructions at a time into machine language is called", {"A. CPU", "B. Interpreter", "C. Compiler", "D. Simulator"}, 'B'};
        questions[9] = {"NTFS stands for?", {"A. New Trend File Saving", "B. Network File Saving", "C. New Technology File System", "D. None Of These"}, 'C'};
        questions[10] = {"Which variable type can have only two possible values?", {"A. integer", "B. string", "C. double", "D. bool"}, 'D'};
        questions[11] = {"In C++, a function name must be followed by", {"A. braces", "B. parentheses", "C. statement", "D. variable name"}, 'B'};
        questions[12] = {"Consider the main body of a program, string a = “4”; string b = “8”; string c = a + b; cout << c << endl; If the program is run, what will be displayed on the screen?", {"A. 4", "B. 8", "C. 12", "D. 48"}, 'D'};
        questions[13] = {"Internet uses _____ to communicate between devices and networks.", {"A. HTTPS", "B. email", "C. website", "D. internet protocol suite"}, 'D'};
        questions[14] = {"C++ is an object-oriented language, and C, BASIC, and Pascal are _____ languages.", {"A. procedural", "B. scripting", "C. general purpose", "D. web-based"}, 'A'};
        questions[15] = {"The amount of time taken by a device to begin reading data is called", {"A. Seek time", "B. Read time", "C. Access time", "D. Write time"}, 'C'};
        questions[16] = {"The main function of a web server is to store and process", {"A. internet", "B. websites", "C. database", "D. programs"}, 'B'};
        questions[17] = {"Google Language Translator” is an example of the application of", {"A. internet", "B. debugging", "C. computer simulations", "D. machine learning"}, 'B'};
        questions[18] = {"The main function of a web server is to store and process", {"A. internet", "B. websites", "C. database", "D. programs"}, 'D'};
        questions[19] = {"The network in which we connect each node to the network along a single piece of network cable is called", {"A. Bus Network Topology", "B. Star Network Topology", "C. Ring Network Topology", "D. None of these"}, 'D'};

    }

    Question getQuestion(int index) {
        return questions[index];
    }
};

class Answer {
public:
    bool checkAnswer(char userAnswer, char correctAnswer) {
        return toupper(userAnswer) == correctAnswer;
    }
};

class Quiz {
private:
    int score;
    int questionsCount;
    BankQuestions bank;
    Answer answerChecker;
    atomic<bool> timeUp;

public:
    Quiz() : score(0), questionsCount(20), timeUp(false) {}

    void startQuiz() {
        auto startTime = chrono::steady_clock::now();
        thread timerThread([this]() {
            this_thread::sleep_for(chrono::minutes(2));
            timeUp = true;
        });

        for (int i = 0; i < questionsCount && !timeUp; ++i) {
            Question currentQuestion = bank.getQuestion(i);
            cout << "\n\n\t\tQuestion #" << i + 1 << ": " << currentQuestion.question << endl;
            cout << "\t\t" << currentQuestion.options[0] << endl;
            cout << "\t\t" << currentQuestion.options[1] << endl;
            cout << "\t\t" << currentQuestion.options[2] << endl;
            cout << "\t\t" << currentQuestion.options[3] << endl;

            char userAnswer;
            cout << "\t\tEnter the option A / B / C / D(or skip it pressing S):";
            cin >> userAnswer;
            userAnswer = toupper(userAnswer);
            
             if (userAnswer == 'S' || userAnswer == 's') {
                cout << "\n\t\tQuestion skipped!" << endl;
                continue;
            }

            if (userAnswer != 'A' && userAnswer != 'B' && userAnswer != 'C' && userAnswer != 'D') {
                cout << "\n\t\tInvalid option! Please enter A, B, C, or D." << endl;
                --i;
                continue;
            }

            if (userAnswer != 'S' && userAnswer != 's') {
                if (answerChecker.checkAnswer(userAnswer, currentQuestion.correctAnswer)) {
                    score++;
                    cout << "\n\t\tCorrect! You chose the right option." << endl;
                } else {
                    cout << "\n\t\tWrong! The correct option was " << currentQuestion.correctAnswer << "." << endl;
               
			    }
             getch();   
            }
             
             system("cls");
        }
    
    

        auto endTime = chrono::steady_clock::now();
        auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

        cout << "Test completed in " << elapsedSeconds << " seconds." << endl;
        showResult();

        timerThread.join(); 
    }

    void showResult() {
        cout << "\n\t\tResults:" << endl;
        cout << "\t\tStudent Score: " << score << " out of " << questionsCount << endl;
        int notAttempted = questionsCount - score;
        if (notAttempted > 0) {
            cout << "\t\tWrong Questions : " << notAttempted << endl;
        }

        if (score >= questionsCount / 2) {
            cout << "\t\tCongratulations! You have passed the test." << endl;
        } else {
            cout << "\t\tSorry, you have failed. Best of luck next time." << endl;
        }
    }
};

class User {
private:
    string name;
    string fatherName;
    double rollNo;

    bool isValidName(const string& input) {
        for (char c : input) {
            if (!isalpha(c) && !isspace(c)) {
                return false;
            }
        }
        return true;
    }
    
    bool isValidfatherName(const string& input) {
        for (char c : input) {
            if (!isalpha(c) && !isspace(c)) {
                return false;
            }
        }
        return true;
    }

public:
    void addInfo() {
        cout << "\n" << endl;
        cout << "   Welcome To The University Entry Test!\n" << endl;
        cout << "\n" << endl;

        while (true) {
            try {
                cout << "\n\t\tEnter Your Name: ";
                getline(cin, name);

                if (!isValidName(name)) {
                    throw invalid_argument("Invalid input. Please enter a valid name containing only alphabets and spaces.");
                }

                break;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

   while (true) {
            try {
                cout << "\n\t\tEnter Your Father's Name: ";
                cin.ignore();
                getline(cin, fatherName);

                if (!isValidName(fatherName)) {
                    throw invalid_argument("Invalid input. Please enter a valid name containing only alphabets and spaces.");
                }

                break;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

        while (true) {
            try {
                cout << "\n\t\tEnter Your Roll Number: ";
                cin >> rollNo;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw invalid_argument("Invalid input. Please enter a valid roll number.");
                }

                break;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

        system("cls");

        cout << "\n\n\n\t\tDear " << name << ", Your Test is Starting!\n" << endl;
    }

    string getName() const {
        return name;
    }
};
int main() {
    User user;
    user.addInfo();

    Quiz entryTest;

    this_thread::sleep_for(chrono::seconds(1));

    thread timerThread([&entryTest]() {
        this_thread::sleep_for(chrono::minutes(2));
        entryTest.showResult();
        exit(0);
    });

    entryTest.startQuiz();
    timerThread.join();

    return 0;
}