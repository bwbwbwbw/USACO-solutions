/*
 ID: vistasw2
 PROG: stamps
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int INFINITE = 0xFFFFFF;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("stamps.in");
    fout.open("stamps.out");

    // f[i]: 得到面值 i 最少使用的方案数
    
    int k, n;
    fin >> k >> n;

    int s[n];
    int maxV = 0;
    for (int i = 0; i < n; ++i) {
        fin >> s[i];
        if (s[i] > maxV) {
            maxV = s[i];
        }
    }

    int maxI = maxV * k + 1;
    int f[maxI];
    fill_n(f, maxI, 0);
    for (int i = 0; i < n; ++i) {
        f[s[i]] = 1;
    }

    if (f[1] == 0) {
        fout << 0 << endl;
        return 0;
    }

    for (int i = 2; i <= maxI; ++i) {
        if (f[i] == 0) {
            int min = INFINITE;
            for (int j = 0; j < n; ++j) {
                if (i - s[j] >= 0) {
                    if (f[i - s[j]] + 1 < min) {
                        min = f[i - s[j]] + 1;
                    }
                }
            }
            if (min == INFINITE || min > k) {
                fout << i - 1 << endl;
                return 0;
            } else {
                f[i] = min;
            }
        }
    }

    fout << maxI - 1 << endl;
    return 0;
}