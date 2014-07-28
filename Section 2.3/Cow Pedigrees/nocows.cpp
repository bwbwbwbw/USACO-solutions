/*
 ID: vistasw2
 PROG: nocows
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

const int p = 9901;

int main()
{
    fin.open("nocows.in");
    fout.open("nocows.out");

    int n, k;
    fin >> n >> k;

    int f[201][101];
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            f[i][j] = 0;
        }
    }
    for (int j = 1; j <= k; ++j) {
        f[1][j] = 1;
    }

    for (int i = 3; i <= n; i += 2) {
        for (int j = 1; j <= k; ++j) {
            for (int t = 1; t <= i - 2; t += 2) {
                f[i][j] += f[t][j - 1] * f[i - 1 - t][j - 1];
                f[i][j] %= p;
            }
        }
    }

    fout << (f[n][k]-f[n][k-1]+p)%p << endl;

    return 0;
}