#include <iostream>
#include <string> 
#include<vector>
#include<map>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<math.h>
#include <cstdlib>
#include <time.h>
using namespace std;

char board[9]{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

void UserInput() {
    bool check = true;
    int move;

    do {
        cout << "\nPlease enter a number between 1 & 9(inclusive): ";
        cin >> move;

        if (board[move - 1] != ' ') {
            cout << "Field not Empty, please select a different position.\n";
        }
        else {
            board[move - 1] = 'X';
            check = false;
        }

    } while (check);
}

void PrintBoard() {
    for (int i = 0; i < 9; i += 3) {
        for (int j = i; j < i + 3; j++) {
            cout << "| " << board[j] << " |";
        }
        cout << "\n -------------- \n";
    }
}

bool IfEqual(char x, char y, char z) {
    if (x == y && x == z && x != ' ') {
        return true;
    }
    return false;
}

int CheckWinner() {
    //  2: X winner
    // -2: O winner
    //  0: Tie
    //  1: No winner

    // For rows
    for (int i = 0; i < 9; i += 3) {
        if (IfEqual(board[i], board[i + 1], board[i + 2])) {
            return board[i] == 'X' ? 2 : -2;
        }
    }

    // For cols
    for (int i = 0; i < 3; i++) {
        if (IfEqual(board[i], board[i + 3], board[i + 6])) {
            return board[i] == 'X' ? 2 : -2;
        }
    }

    // Diameter 1
    if (IfEqual(board[0], board[4], board[8])) {
        return board[0] == 'X' ? 2 : -2;
    }

    // Diameter 2
    if (IfEqual(board[2], board[4], board[6])) {
        return board[2] == 'X' ? 2 : -2;
    }

    // For Tie Case
    bool tie = true;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            tie = false;
        }
    }
    if (tie)
        return 0;

    // Else
    return 1;
}

int minimax(int depth, bool isMaximizing, bool firstTime = true) {
    int result = CheckWinner();
    if (depth == 0 || result != 1) {
        return result;
    }

    if (isMaximizing) {
        int finalScore = -10;
        int finalI;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(depth - 1, false, false);
                board[i] = ' ';
                if (score > finalScore) {
                    finalScore = score;
                    finalI = i;
                }
                if (firstTime) {
                    cout << "score," << i << ": " << score << "\n";
                }
            }
        }
        if (firstTime) {
            board[finalI] = 'O';
        }
        return finalScore;
    }
    else {
        int finalScore = 10;
        int finalI;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(depth - 1, true, false);
                board[i] = ' ';
                if (score < finalScore) {
                    finalScore = score;
                    finalI = i;
                }
                if (firstTime) {
                    // cout << "score," << i << ": " << score << "\n";
                }
            }
        }
        if (firstTime) {
            board[finalI] = 'O';
        }
        return finalScore;
    }
}

int minimaxPruning(int depth, bool isMaximizing, bool firstTime = true,
    int alpha = -10, int beta = 10) {

    int result = CheckWinner();
    if (depth == 0 || result != 1) {
        return result;
    }

    if (isMaximizing) {
        int finalScore = -10;
        int finalI;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimaxPruning(depth - 1, false, false, alpha, beta);
                board[i] = ' ';
                if (score > finalScore) {
                    finalScore = score;
                    finalI = i;
                }
                if (firstTime) {
                    cout << "score," << i << ": " << score << "\n";
                }

                alpha = max(alpha, finalScore);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        if (firstTime) {
            board[finalI] = 'O';
        }
        return finalScore;
    }
    else {
        int finalScore = 10;
        int finalI;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimaxPruning(depth - 1, true, false, alpha, beta);
                board[i] = ' ';
                if (score < finalScore) {
                    finalScore = score;
                    finalI = i;
                }
                if (firstTime) {
                    // cout << "score," << i << ": " << score << "\n";
                }
                beta = min(beta, finalScore);
                if (beta <= alpha) {
                    break;
                }
            }
        }
        if (firstTime) {
            board[finalI] = 'O';
        }
        return finalScore;
    }
}

void UserInterface() {

    cout << "1) MINIMAX without Alpha-Beta pruning\n2) MINIMAX with Alpha-Beta pruning\n";
    cout << "Please select corresponding number for the function you want: ";
    int choice;
    cin >> choice;



    bool checkWinner = false;
    while (!checkWinner) {
        UserInput();
        int result;
        if (choice == 1) {
            result = minimax(8, false);
        }
        else if (choice == 2) {
            result = minimaxPruning(8, false);
        }
        else {
            cout << "Incorrect Number selected for function. Terminating Program...\n";
            return;
        }

        PrintBoard();
        // cout << "result: " << result << "\n";
        checkWinner = CheckWinner() != 1;
    }

    int result = CheckWinner();
    if (result == 0) {
        cout << "Tie \n";
    }
    else {
        cout << ((result == 2) ? "X" : "O") << " player wins \n";
    }
}

int main() {

    UserInterface();

    return 0;
}