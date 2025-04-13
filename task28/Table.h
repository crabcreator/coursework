#ifndef TABLE_H
#define TABLE_H

#include <iostream>
using namespace std;

class Table {
    string block[9][9];
public:
    Table();
    Table(string arr[9][9]);
    void solve();
    bool check_touching(); // checks whether shaded cells are touching. If they're not - returns true
    bool check_repetitions(); // checks repetitions of numbers in rows, columns and 3x3 blocks
    bool check_space(); // checks non-shaded cells to share common continuous space
    bool check(); // checks all of the parameters
    void print();
};
#endif