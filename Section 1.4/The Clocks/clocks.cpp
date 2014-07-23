/*
ID: vistasw2
PROG: clocks
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int clocks;

/*

000 - 12
001 -  3
010 -  6
011 -  9

00000 xxx xxx xxx xxx xxx xxx xxx xxx xxx
        A   B   C   D   E   F   G   H   I
MOVE
1     001 001 000 001 001 000 000 000 000 = 18911232
2     001 001 001 000 000 000 000 000 000 = 19136512
3     000 001 001 000 001 001 000 000 000 = 2363904
4     001 000 000 001 000 000 001 000 000 = 16810048
5     000 001 000 001 001 001 000 001 000 = 2134536
6     000 000 001 000 000 001 000 000 001 = 262657
7     000 000 000 001 001 000 001 001 000 = 36936
8     000 000 000 000 000 000 001 001 001 = 73
9     000 000 000 000 001 001 000 001 001 = 4617

BITMASK
LOW   011 011 011 011 011 011 011 011 011 = 57521883

*/

int clock_map[13] = {0, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0, 0, 0};
int rotation[10] = {0, 18911232, 19136512, 2363904, 16810048, 2134536, 262657, 36936, 73, 4617};
const int rotation_mask = 57521883;

inline void transform(int method)
{
    clocks = (clocks + rotation[method]) & rotation_mask;
}

int main()
{
    ifstream fin("clocks.in");
    ofstream fout("clocks.out");

    clocks = 0;
    for (int i = 0; i < 9; ++i) {
        int single;
        fin >> single;
        clocks = (clocks << 3) | clock_map[single];
    }

    /*
        iterate how much times each move
        000000000 = 0
        333333333 = 262143
     */
    for (int i = 0; i <= 262143; ++i) {
        int moves = i;
        int original = clocks;
        for (int move = 1; move <= 9; ++move) {
            int times = moves & 3;  //times = moves % 4;
            moves = moves >> 2;     //moves = moves / 4;
            for (int j = 0; j < times; ++j) {
                transform(move);
            }
        }

        // output
        if (clocks == 0) {
            vector<int> output;
            moves = i;
            for (int move = 1; move <= 9; ++move) {
                int times = moves & 3;
                moves = moves >> 2;
                for (int j = 0; j < times; ++j) {
                    output.push_back(move);
                }
            }

            for (int i = 0; i < output.size() - 1; ++i) {
                fout << output[i] << " ";
            }
            fout << output[output.size() - 1] << endl;

            return 0;
        }

        clocks = original;
    }

    return 0;
}