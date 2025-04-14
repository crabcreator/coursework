#include "Board.h"

Board::Board() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = "";
        }
    } 
}
Board::Board(string arr[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            block[i][j] = arr[i][j];
        }
    } 
}
void Board::solve() {
    // iterating over left top cells of 3x3 blocks
    for (int i = 0; i < 9; i+=3) {
        for (int j = 0; j < 9; j+=3) {
            // iterating over cells in ONE 3x3 block
            for (int row = i; row-i < 3; row++) {
                for (int col = j; col-j < 3; col++) {
                    // check repetitions in 3x3 block
                    for (int k = i; k-i < 3; k++) {
                        for (int l = j; l-j < 3; l++) {
                            // check whether cells are not shaded and we are not comparing the cell with itself
                            if (block[row][col].length() == 1 && block[k][l].length() == 1 && (row!=k || col!=l)) {
                                // if number in cells are equal - shade
                                if (block[row][col] == block[k][l]) {
                                    block[row][col] += '#';
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
bool Board::check_touching() {
    return true;
}
bool Board::check_repetitions() {
    return true;
}
bool Board::check_space() {
    return true;
}
bool Board::check() {
    if (!check_touching()) {
        cout << "!check_touching()\n";
        return false;
    } else if (!check_repetitions()) {
        cout << "!check_repetiotions()\n";
        return false;
    } else if (!check_space()) {
        cout << "!check_space()\n";
        return false;
    }
    return true;
}
// print the board with separate 3x3 blocks
void Board::print() {
    for (int i = 0; i < 9; i++) {
        if ((i%3)==0 && i!=0 && i!=8) {
            cout << "\033[1m├───┼───┼───┼───┼───┼───┼───┼───┼───┤\n";
        } else if ((i%3)==0) {
            cout << "\033[1m┌───┬───┬───┬───┬───┬───┬───┬───┬───┐\n";
        } else {
            cout << "\033[1m├\033[0m───┼───┼───\033[1m┼\033[0m───┼───┼───\033[1m┼\033[0m───┼───┼───\033[1m┤\n";
        }
        cout << "│\033[0m";
        for (int j = 0; j < 9; j++) {
            if (block[i][j].length() == 1) {
                cout << " " << block[i][j] << " ";
            } else {
                cout << "\033[7m " << block[i][j][0] << " \033[0m";
            }
            if ((j+1)%3==0) {
                cout << "\033[1m│\033[0m";
            } else {
                cout << "│";
            }
        }
        cout << endl;
    }
    cout << "\033[1m└───┴───┴───┴───┴───┴───┴───┴───┴───┘\033[0m\n";
}