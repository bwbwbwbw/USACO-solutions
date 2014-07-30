/*
 ID: vistasw2
 PROG: ttwo
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

ifstream fin;
ofstream fout;

struct pos
{
    int row;
    int col;
};

pos directions[4] = {
    {-1, 0},    // north
    {0, 1},     // east
    {1, 0},     // south
    {0, -1},    // west
};

char m[12][12];
pos farm, cow;
int farm_direction = 0;
int cow_direction = 0;

set<int> history;

int makeState()
{
    int state = 0;
    state = state | (farm.row);
    state = state | (farm.col << 4);
    state = state | (farm_direction << 8);
    state = state | (cow.row << 10);
    state = state | (cow.col << 14);
    state = state | (cow_direction << 18);
    return state;
}

int main()
{
    fin.open("ttwo.in");
    fout.open("ttwo.out");

    for (int i = 0; i <= 11; ++i) {
        m[i][0] = '*';
        m[i][11] = '*';
        m[0][i] = '*';
        m[11][i] = '*';
    }

    for (int row = 1; row <= 10; ++row) {
        for (int col = 1; col <= 10; ++col) {
            m[row][col] = fin.get();
            if (m[row][col] == 'F') {
                farm.row = row;
                farm.col = col;
            } else if (m[row][col] == 'C') {
                cow.row = row;
                cow.col = col;
            }
        }

        fin.get();
    }

    int step = 0;
    bool ok = false;
    while (true) {
        step++;
        if (m[farm.row + directions[farm_direction].row][farm.col + directions[farm_direction].col] == '*') {
            farm_direction++;
            farm_direction %= 4;
        } else {
            farm.row += directions[farm_direction].row;
            farm.col += directions[farm_direction].col;
        }
        if (m[cow.row + directions[cow_direction].row][cow.col + directions[cow_direction].col] == '*') {
            cow_direction++;
            cow_direction %= 4;
        } else {
            cow.row += directions[cow_direction].row;
            cow.col += directions[cow_direction].col;
        }
        int state = makeState();
        if (history.find(state) == history.end()) {
            history.insert(state);
        } else {
            ok = false;
            break;
        }
        if (farm.row == cow.row && farm.col == cow.col) {
            ok = true;
            break;
        }
    }

    if (!ok) {
        fout << 0 << endl;
    } else {
        fout << step << endl;
    }

    return 0;
}