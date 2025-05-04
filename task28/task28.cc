#include <iostream>
#include "Board.h"
using namespace std;

int main() {
    string block[9][9] = {
        {"3", "9", "6", "2", "5", "1", "6", "8", "7"},
        {"6", "1", "2", "7", "3", "3", "4", "9", "5"},
        {"7", "3", "9", "8", "6", "9", "7", "2", "5"},
        {"3", "7", "5", "1", "8", "4", "2", "7", "8"},
        {"9", "8", "8", "6", "7", "4", "5", "1", "4"},
        {"1", "5", "9", "3", "5", "8", "1", "6", "4"},
        {"5", "4", "1", "2", "2", "6", "8", "7", "9"},
        {"2", "2", "3", "5", "4", "3", "6", "5", "1"},
        {"4", "6", "8", "7", "1", "9", "7", "3", "2"}
    };
    Board board(block);
    board.print();
    char answer[10];
    bool running = true;
    while(running) {
        cout << "Choose an option:\n";
        cout << "1 - solve it yourself\t2 - solve with computer\n3 - exit\n";
        cin >> answer;
        int option = atoi(answer);
        switch(option) {
            case 1:
                board.solve_user();
                board.print();
                running = false;
                break;
            case 2:
                board.solve();
                board.print();
                running = false;
                break;
            case 3:
                cout << "Bye!\n";
                running = false;
                break;
            default:
                cout << "Unknown option '" << answer << "'\n";
        }
        cin.ignore();
    }
    return 0;
}