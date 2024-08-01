/**
 * Name: Xander Siodlarz
 * Filename: project4_siodlarz_acs0244.cpp
 * ID: acs0244
 * Download file, then compile and run code on CLion
 * Help: Stack Overflow, Bitdegree.org,
 */

#include <iostream>
#include <assert.h>
using namespace std;

struct Trivia {
    struct TriviaNode {
        string question;
        string answer;
        int score;
        TriviaNode *next;

        TriviaNode(string q, string a, int s) {
            question = q;
            answer = a;
            score = s;
            next = nullptr;
        }
    };


    // List Variables
    TriviaNode *first;
    TriviaNode *last;
    int size;
    int score;

    Trivia() {
        first = nullptr;
        last = nullptr;
        size = 0;
        score = 0;
    }
    int askQuestion(Trivia triviaNodes, int numAsked){

        string userAnswer = "";
        if (numAsked < 1) {
            cout << "Warning - the number of trivia to be asked must equal to or be larger than 1." << endl;
            return 1;
        }
        else if (size < numAsked) {
            cout << "Warning - there is only " << size << " trivia questions in the list." << endl;
            return 1;
        }
        else {
            TriviaNode *t = triviaNodes.first;
            for(int i = 0; i < numAsked; i++){
                if(i ==  0){
                    cout << "\nQuestion: " << t->question;
                    cout << "\nAnswer: ";
                    getline(cin, userAnswer);
                    if (userAnswer.compare(t->answer) == 0) {
                        cout << "Your answer is correct. You receive " << t->score << " points." << endl;
                        cout << "Your total points: " << score << "\n";
                        score += t->score;
                    }
                    else {
                        cout << "Your answer is wrong. The correct answer is: " << t->answer << endl;
                        cout << "Your total points: " << score << "\n";
                    }
                }
                else {
                    t = t->next;
                    cout << "\nQuestion: " << t->question;
                    cout << "\nAnswer: ";
                    getline(cin, userAnswer);
                    if (userAnswer.compare(t->answer) == 0) {
                        cout << "Your answer is correct. You receive " << t->score << " points." << endl;
                        cout << "Your total points: " << score << "\n";
                        score += t->score;
                    }
                    else {
                        cout << "Your answer is wrong. The correct answer is: " << t->answer << endl;
                        cout << "Your total points: " << score << "\n";
                    }
                }
            }
        }
        return 0;
    }

    void add(string q, string a, int s) {
        TriviaNode* new_node = new TriviaNode(q, a, s);
        if (size == 0) {
            first = new_node;
        }
        else {
            last->next = new_node;
        }
        last = new_node;
        size++;
    }


    // Prompt user to add a question
    void addQuestion() {
        string q;
        string a;
        string s;
        int score;
        cout << "Enter a question: ";
        getline(cin, q);
        cout << "Enter an answer: ";
        getline(cin, a);
        cout << "Enter award points: ";
        getline(cin, s);
        score = stoi(s);
        add(q, a, score);
    }



    // Initialize a list with some example questions. Currently accepted versions are 0 and 1
    void initial_questions() {
            add("How long was the shortest war on record? (Hint: how many minutes)", "38", 100);
            add("What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)?", "Bank of Germany", 50);
            add("What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)?", "Wii Sports", 20);
    }
};

// Conditions
#define production
//#define UNIT_TESTING

int main() {
    Trivia trivia = Trivia();

#ifdef production
    trivia.initial_questions();
    cout << "*** Welcome to Xander's trivia quiz game ***\n";

    bool anotherQ = true;
    while(anotherQ){
        trivia.addQuestion();
        string userInput = "";
        cout << "Continue? (y/n): ";
        getline(cin, userInput);
        if (userInput.at(0) == 'y' || userInput.at(0) == 'Y') {
            anotherQ = true;
        }
        else if (userInput.at(0) == 'n' || userInput.at(0) == 'N') {
            anotherQ = false;
        }
        else {
            cout << "Invalid Response" << endl;
            userInput = "";
        }
    }

    trivia.askQuestion(trivia,trivia.size);

    cout << "\n*** Thank you for playing the trivia quiz game. Goodbye! ***";
#endif

#ifdef UNIT_TESTING
    cout << "*** This is a debugging version ***" << endl;
        trivia.initial_questions();
        cout << "Unit Test Case 1: Ask no question. The program should give a warning message." << endl;
        int warning = trivia.askQuestion(trivia, 0);
        assert(1 == warning);
        cout << "\nCase 1 Passed" << endl << endl;

        cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
        trivia.askQuestion(trivia, 1);
        assert(trivia.score == 0);
        cout << "\nCase 2.1 passed" << endl << endl;

        cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
        trivia.askQuestion(trivia, 1);
        assert(trivia.score == 100);
        cout << "\nCase 2.2 passed" << endl << endl;

        cout << "Unit Test Case 3: Ask all the questions in the linked list." << endl;
        int played = trivia.askQuestion(trivia,3);
        assert(played == 0);
        cout << "\nCase 3 passed" << endl << endl;

        cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
        warning = trivia.askQuestion(trivia, 5);
        assert(1 == warning);
        cout << "\nCase 4 passed" << endl << endl;

        cout << "*** End of the Debugging Version ***";
#endif
}
