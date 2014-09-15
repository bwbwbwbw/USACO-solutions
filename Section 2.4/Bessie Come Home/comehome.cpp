/*
 ID: vistasw2
 PROG: comehome
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

const int INFINITE = 0xFFFFFF;
const int N = 52;

int charToInt(char c)
{
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else {
        return c - 'A' + 26;
    }
}

char intToChar(int i)
{
    if (i <= 25) {
        return char('a' + i);
    } else {
        return char('A' + (i - 26));
    }
}

int g[N][N];
int ans_min = INFINITE, ans;

int main()
{
    fin.open("comehome.in");
    fout.open("comehome.out");

    int p;
    fin >> p;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            g[i][j] = INFINITE;
        }
    }

    for (int i = 0; i < p; ++i) {
        char _p1, _p2;
        int dis;
        fin >> _p1 >> _p2 >> dis;
        int p1 = charToInt(_p1);
        int p2 = charToInt(_p2);
        if (dis < g[p1][p2]) {
            g[p1][p2] = dis;
            g[p2][p1] = dis;
        }
    }

    for (int i = 0; i < N; ++i) {
        g[i][i] = 0;
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (g[i][k] + g[j][k] < g[i][j]) {
                    g[i][j] = g[i][k] + g[j][k];
                }
            }
        }
    }

    for (int i = 26; i < N - 1; ++i) {
        if (g[i][N-1] < ans_min) {
            ans_min = g[i][N-1];
            ans = i;
        }
    }

    fout << intToChar(ans) << " " << ans_min << endl;

    return 0;
}