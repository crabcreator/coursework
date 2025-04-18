#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
using namespace std;

typedef struct Cell Cell;
struct Cell {
    int row = 0;
    int col = 0;
    bool operator ==(Cell &c) {
        if(row == c.row && col == c.col) {
            return true;
        }
        return false;
    }
};

class Board {
    string block[9][9];
    enum SIDES { LEFT, TOP, RIGHT, BOTTOM }; // is used in some arrays to represent sides around the cell
    vector<Cell> cell; // represents position of one cell. Needed for the correct operation of the reshade() function
    
    bool contains(Cell c); // checks whether vector<Cell> cell contains specified Cell c
    bool has_neighbours(int row, int col); // checks whether cell has a shaded "neighbour"
    bool is_trapped(int row, int col, int size=-1); // side - from which of four sides came the "request"
    bool reshade(int row, int col); // look up for new shading combination. If shaded cell is passed, check whether we can unshade it. For non-shaded cell - the opposite
    bool area_has_num(int row, int col); // check 3x3 area. Returns true if area contains specified non-shaded number
    int get_area(int row, int col); // returns area on the board. 1 - first area, 9 - last area.
public:
    Board();
    Board(string arr[9][9]);
    void solve();
    bool check(int out=0); // checks all of the parameters. out - default argument (whether to print errors)
    void print();
};
#endif