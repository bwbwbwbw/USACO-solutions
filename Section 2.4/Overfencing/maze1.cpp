/*
 ID: vistasw2
 PROG: maze1
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct pos
{
    int row;
    int col;
};

ifstream fin;
ofstream fout;

int W, H, w, h;
char m[82][205] = {{0}};
pos e[2];
int v[82][205] = {{0}};

pos moves[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

int steps[82][205] = {{0}};

void clearMap()
{
    for (int i = 0; i < 82; ++i) {
        for (int j = 0; j < 204; ++j) {
            v[i][j] = 0;
        }
    }
}

void search(int row, int col, int step)
{
    // if this cell is already visited and has a shorter step value, return
    if (steps[col][row] == 0 || step < steps[col][row]) {
        steps[col][row] = step;
    } else {
        return;
    }

    v[col][row] = 1;

    int availableMove = 0;
    for (int i = 0; i < 4; ++i) {
        if (m[col + moves[i].col][row + moves[i].row] != '*' && v[col + moves[i].col][row + moves[i].row] == 0) {
            availableMove++;
            search(row + moves[i].row, col + moves[i].col, step + 1);
        }
    }

    v[col][row] = 0;
}

int main()
{
    fin.open("maze1.in");
    fout.open("maze1.out");

    fin >> W >> H;
    w = 2 * W + 1;
    h = 2 * H + 1;
    for (int i = 0; i <= w + 1; ++i) {
        m[i][0] = '*';
        m[i][h+1] = '*';
    }
    for (int i = 0; i <= h + 1; ++i) {
        m[0][i] = '*';
        m[w+1][i] = '*';
    }

    fin.get();

    for (int row = 1; row <= h; ++row) {
        for (int col = 1; col <= w; ++col) {
            char c = fin.get();
            if (c == ' ') {
                m[col][row] = '.';
            } else {
                m[col][row] = '*';
            }
        }
        fin.get();
    }

    // find two exits
    int exitIndex = 0;
    for (int i = 1; i <= w; ++i) {
        if (m[i][1] == '.') {
            e[exitIndex].row = 1;
            e[exitIndex].col = i;
            exitIndex++;
        }
        if (m[i][h] == '.') {
            e[exitIndex].row = h;
            e[exitIndex].col = i;
            exitIndex++;
        }
    }
    for (int i = 1; i <= h; ++i) {
        if (m[1][i] == '.') {
            e[exitIndex].row = i;
            e[exitIndex].col = 1;
            exitIndex++;
        }
        if (m[w][i] == '.') {
            e[exitIndex].row = i;
            e[exitIndex].col = w;
            exitIndex++;
        }
    }

    for (int i = 0; i < 2; ++i) {
        search(e[i].row, e[i].col, 0);
    }

    int maxStep = 0;

    for (int i = 2; i < h; ++i) {
        for (int j = 2; j < w; ++j) {
            if (steps[j][i] > maxStep) {
                maxStep = steps[j][i];
            }
        }
    }

    fout << ((maxStep + 1) >> 1) << endl;
    
    return 0;
}