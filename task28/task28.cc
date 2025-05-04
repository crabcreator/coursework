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
    Board temp(block);
    temp.print();
    char answer[10];
    bool running = true;
    cout << "Choose an option:\n";
    cout << "1 - enter board from keyboard\t2 - keep prepared board\n";
    cin >> answer;
    cin.ignore();
    if (strcmp(answer, "1")==0) {
        char line[50];
        char c;
        cout << "Enter one row of 9 digits per line (e.g '123456789')\n";
        for (int i = 0; i < 9; i++) {
            cout << "Enter row #" << i+1 << ":\n";
            cin.getline(line, 50);
            if (strlen(line) == 9) {
                for (int j = 0; j < 9; j++) {
                    c = line[j];
                    if ((int)(c-'0') < 1 || (int)(c-'0') > 9) {
                        cout << "Number in cell must be in range 1-9\n";
                        i--; // fill the row again
                        break;
                    } else {
                        block[i][j] = c;
                    }
                }
            } else {
                cout << "Line must contain 9 digits\n";
                i--;
            }
        }
    }
    Board board(block);
    while (running) {
        cout << "Choose an option:\n";
        cout << "1 - solve it yourself\t2 - solve with computer\n3 - exit\n";
        cin >> answer;
        int option = atoi(answer);
        switch (option) {
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