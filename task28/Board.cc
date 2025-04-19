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
                                    if (has_neighbours(row, col)) {
                                        block[k][l] += '#';
                                    } else {
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
    // check rows and columns
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int row = i+1; row < 9; row++) {
                if (block[i][j].length() == 1 && block[row][j].length() == 1 && row != i) {
                    // if number in cells are equal - shade
                    if (block[i][j] == block[row][j]) {
                        if (has_neighbours(i, j)) {
                            block[row][j] += '#';
                        } else {
                            block[i][j] += '#';
                        }
                    }
                }
            }
            for (int col = j+1; col < 9; col++) {
                if (block[i][j].length() == 1 && block[i][col].length() == 1 && col != j) {
                    // if number in cells are equal - shade
                    if (block[i][j] == block[i][col]) {
                        if (has_neighbours(i, j)) {
                            block[i][col] += '#';
                        } else {
                            block[i][j] += '#';
                        }
                    }
                }
            }
        }
    }
    // check for "trapped" non-shaded cells
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(is_trapped(i, j)) {
                bool sides[4]{false}; // which sides can be reshaded.
                if (i == 0) {
                    if (block[i+1][j].length() > 1) sides[BOTTOM] = true;
                }  else if (i == 8) {
                    if (block[i-1][j].length() > 1) sides[TOP] = true;
                } else {
                    if (block[i+1][j].length() > 1) sides[BOTTOM] = true;
                    if (block[i-1][j].length() > 1) sides[TOP] = true;
                }
                if (j == 0) {
                    if (block[i][j+1].length() > 1) sides[RIGHT] = true;
                } else if (j == 8) {
                    if (block[i][j-1].length() > 1) sides[LEFT] = true;
                } else {
                    if (block[i][j+1].length() > 1) sides[RIGHT] = true;
                    if (block[i][j-1].length() > 1) sides[LEFT] = true;
                }
                bool reshaded = false;
                if (sides[LEFT]) {
                    reshaded = reshade(i, j-1);
                }
                if (!reshaded && sides[TOP]) {
                    reshaded = reshade(i-1, j);
                }
                if (!reshaded && sides[RIGHT]) {
                    reshaded = reshade(i, j+1);
                }
                if (!reshaded && sides[BOTTOM]) {
                    reshaded = reshade(i+1, j);
                }
            }
        }
    }
    check(1);
}
bool Board::has_neighbours(int row, int col) {
    if (row == 0) {
        if (block[row+1][col].length() > 1) {
            return true;
        }
    } else if (row == 8) {
        if (block[row-1][col].length() > 1) {
            return true;
        }
    } else {
        if (block[row+1][col].length() > 1 || block[row-1][col].length() > 1) {
            return true;
        }
    }
    if (col == 0) {
        if (block[row][col+1].length() > 1) {
            return true;
        }
    } else if (col == 8) {
        if (block[row][col-1].length() > 1) {
            return true;
        }
    } else {
        if (block[row][col+1].length() > 1 || block[row][col-1].length() > 1) {
            return true;
        }
    }
    return false;
}
bool Board::is_trapped(int row, int col, int side) {
    if(block[row][col].length() == 1) {
        // first - check is this cell is trapped directly
        bool shaded[] = {false, false, false, false}; // array that represents 4 sides around the cell
        if (row == 0) {
            shaded[TOP] = true;
            if (block[row+1][col].length() > 1) {
                shaded[BOTTOM] = true;
            }
        } else if (row == 8) {
            shaded[BOTTOM] = true;
            if (block[row-1][col].length() > 1) {
                shaded[TOP] = true;
            }
        } else {
            if (block[row+1][col].length() > 1) {
                shaded[BOTTOM] = true;
            }
            if (block[row-1][col].length() > 1) {
                shaded[TOP] = true;
            }
        }
        if (col == 0) {
            shaded[LEFT] = true;
            if (block[row][col+1].length() > 1) {
                shaded[RIGHT] = true;
            }
        } else if (col == 8) {
            shaded[RIGHT] = true;
            if (block[row][col-1].length() > 1) {
                shaded[LEFT] = true;
            }
        } else {
            if (block[row][col+1].length() > 1) {
                shaded[RIGHT] = true;
            }
            if (block[row][col-1].length() > 1) {
                shaded[LEFT] = true;
            }
        }
        if (side != -1) {
            shaded[side] = true; // the side from which came the "request" is also "trapped"
        }
        if (shaded[LEFT] && shaded[TOP] && shaded[RIGHT] && shaded[BOTTOM]) {
            return true;
        } else {
            int count = 0;
            for (int i = 0; i < 4; i++) {
                if (!shaded[i]) count++;
            }
            if (count > 1) return false;
            // second - check whether sell is trapped indirectly (whether other cells are trapped)
            if (!shaded[LEFT]) {
                if (is_trapped(row, col-1, RIGHT)) {
                    return true;
                }
            } else if (!shaded[TOP]) {
                if (is_trapped(row-1, col, BOTTOM)) {
                    return true;
                }
            } else if (!shaded[RIGHT]) {
                if (is_trapped(row, col+1, LEFT)) {
                    return true;
                }
            } else if (!shaded[BOTTOM]) {
                if (is_trapped(row+1, col, TOP)) {
                    return true;
                }
            }
        } 
    }
    return false;
}
bool Board::reshade(int row, int col) {
    if (contains({row, col})) {
        return false;
    }
    cell.push_back({row, col});
    if (block[row][col].length() == 1) { // cell is non-shaded. We must SHADE this cell
        // 1. If we shade this cell, check whether this will affect general state (i.e. search for the same number in rows, columns and this 3x3 area, check whether this cell has "neighbours" and check whether this will create "trapped" cells)
        // 1.1. Check for "neighbours"
        bool can_reshade = true;
        if (!has_neighbours(row, col)) {
            block[row][col] += '#';
            return true;
        } else {
            can_reshade = false;
        }
        // 1.2. Check whether shading this cell will create a "trapped" cell
        if (row == 0) {
            if (is_trapped(row+1, col, TOP)) can_reshade = false;
        } else if (row == 8) {
            if (is_trapped(row-1, col, BOTTOM)) can_reshade = false;
        } else {
            if (is_trapped(row+1, col, TOP) || is_trapped(row-1, col, BOTTOM)) can_reshade = false;
        }
        if (col == 0) {
            if (is_trapped(row, col+1, LEFT)) can_reshade = false;
        } else if (col == 8) {
            if (is_trapped(row, col-1, RIGHT)) can_reshade = false;
        } else {
            if (is_trapped(row, col+1, LEFT) || is_trapped(row, col-1, RIGHT)) can_reshade = false;
        }
        // 2. If we cannot unshade this cell directly, search recursively for cell that can be unshaded
        if (can_reshade) {
            block[row][col] += '#';
            return true;
        } else {
            // check whether we can reshade "neighbours"
            if (row == 0) {
                if (block[row+1][col].length() > 1) {
                    if (reshade(row+1, col) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            } else if (row == 8) {
                if (block[row-1][col].length() > 1) {
                    if (reshade(row-1, col) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            } else {
                if (block[row+1][col].length() > 1) {
                    if (reshade(row+1, col) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
                if (block[row-1][col].length() > 1) {
                    if (reshade(row-1, col) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            }
            if (col == 0) {
                if (block[row][col+1].length() > 1) {
                    if (reshade(row, col+1) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            } else if (col == 8) {
                if (block[row][col-1].length() > 1) {
                    if (reshade(row, col-1) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            } else {
                if (block[row][col+1].length() > 1) {
                    if (reshade(row, col+1) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
                if (block[row][col-1].length() > 1) {
                    if (reshade(row, col-1) && !has_neighbours(row, col)) {
                        block[row][col] += '#';
                        return true;
                    }
                }
            }
        }
    } else { // cell is shaded. We must UNSHADE this cell
        // check row
        for (int j = 0; j < 9; j++) {
            if (j != col && block[row][col][0] == block[row][j][0] && block[row][j].length() == 1) {
                if (!reshade(row, j) || area_has_num(row, col)) {
                    return false;
                }
            }
        }
        // check column
        for (int i = 0; i < 9; i++) {
            if (i != row && block[row][col][0] == block[i][col][0]  && block[i][col].length() == 1) {
                if (reshade(i, col) && !area_has_num(row, col)) {
                    block[row][col].pop_back();
                    return true;
                } else return false;
            }
        }
        // check 3x3 area
        if (area_has_num(row, col)) {
            int area = get_area(row, col);
            int count = 0;
            for (int i = 0; i < 9; i+=3) {
                for (int j = 0; j < 9; j+=3) {
                    count++;
                    if (count == area) {
                        for (int k = i; k-i < 3; k++) {
                            for (int l = j; l-j < 3; l++) {
                                if (k!=row && l!=col && block[k][l][0]==block[row][col][0] && block[k][l].length()==1) {
                                    if (!reshade(k, l)) {
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        block[row][col].pop_back();
        return true;
    }
    return false;
}
bool Board::area_has_num(int row, int col) {
    char num = block[row][col][0];
    int area = get_area(row, col);
    int count = 0;
    for (int i = 0; i < 9; i+=3) {
        for (int j = 0; j < 9; j+=3) {
            count++;
            if (count == area) {
                for (int k = i; k-i < 3; k++) {
                    for (int l = j; l-j < 3; l++) {
                        if(k != row && l != col && block[k][l][0] == num && block[k][l].length() == 1) {
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    return false;
}
int Board::get_area(int row, int col) {
    if (row >= 0 && row <= 2) {
        if (col >= 0 && col <= 2) {
            return 1;
        } else if (col >= 3 && col <= 5) {
            return 2;
        } else {
            return 3;
        }
    } else if (row >= 3 && row <= 5) {
        if (col >= 0 && col <= 2) {
            return 4;
        } else if (col >= 3 && col <= 5) {
            return 5;
        } else {
            return 6;
        }
    } else {
        if (col >= 0 && col <= 2) {
            return 7;
        } else if (col >= 3 && col <= 5) {
            return 8;
        } else {
            return 9;
        }
    }
    cout << "\033[38;5;196mERROR! ROW: " << row << " COL: " << col << "\033[0m\n";
    exit(1);
    return -1;
}
bool Board::contains(Cell c) {
    for (Cell i : cell) {
        if (i == c) return true;
    }
    return false;
}
bool Board::check(int out) {
    // check for repetitions in 3x3 blocks and "trapped" cells
    bool error = false;
    for (int i = 0; i < 9; i+=3) {
        for (int j = 0; j < 9; j+=3) {
            for (int row = i; row-i < 3; row++) {
                for (int col = j; col-j < 3; col++) {
                    if (is_trapped(row, col)) {
                        if (out) {
                            cout << "\033[38;5;196mError in row " << row << " column " << col << " with number " << block[row][col] << " (trapped)\033[0m\n";
                        }
                        error = true;
                    }
                    for (int k = i; k-i < 3; k++) {
                        for (int l = j; l-j < 3; l++) {
                            if (block[row][col].length() == 1 && block[k][l].length() == 1 && (row!=k || col!=l)) {
                                if (block[row][col] == block[k][l]) {
                                    if (out) {
                                        cout << "\033[38;5;196mError in row " << row << " column " << col << " with number " << block[row][col] << " (repeated in area " << get_area(row, col) << ")\033[0m\n";
                                    }
                                    error = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // check for repetitions in rows and columns
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            for (int row = i+1; row < 9; row++) {
                if (block[i][j].length() == 1 && block[row][j].length() == 1 && row != i) {
                    if (block[i][j] == block[row][j]) {
                        if (out) {
                            cout << "\033[38;5;196mError in column " << j << " with number " << block[i][j] << " (repeated)\033[0m\n";
                        }
                        error = true;
                    }
                }
            }
            for (int col = j+1; col < 9; col++) {
                if (block[i][j].length() == 1 && block[i][col].length() == 1 && col != j) {
                    if (block[i][j] == block[i][col]) {
                        if (out) {
                            cout << "\033[38;5;196mError in row " << i << " with number " << block[i][j] << " (repeated)\033[0m\n";
                        }
                        error = true;
                    }
                }
            }
        }
    }
    if (!error) {
        cout << "\033[38;5;118mSolved!\033[0m\n";
    }
    return !error;
}
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