/*
ID: vistasw2
PROG: numtri
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
    ifstream fin("numtri.in");
    ofstream fout("numtri.out");

    int r;
    fin >> r;

    int m[1002][1002];
    int f[1002][1002];

    for (int i = 0; i <= r + 1; ++i) {
        for (int j = 0; j <= r + 1; ++j) {
            f[i][j] = 0;
        }
    }

    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= i; ++j) {
            fin >> m[i][j];
        }
    }

    f[1][1] = m[1][1];

    for (int i = 2; i <= r; ++i) {
        for (int j = 1; j <= i; ++j) {
            f[i][j] = max(f[i-1][j], f[i-1][j-1]) + m[i][j];
        }
    }

    int result = 0;
    for (int i = 1; i <= r; ++i) {
        if (f[r][i] > result) {
            result = f[r][i];
        }
    }

    fout << result << endl;

    return 0;
}