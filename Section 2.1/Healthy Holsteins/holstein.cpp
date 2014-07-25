/*
 ID: vistasw2
 PROG: holstein
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("holstein.in");
    fout.open("holstein.out");
    
    int v;
    int require[1000];
    int g;
    int value[15][1000];

    fin >> v;
    for (int i = 0; i < v; ++i) {
        fin >> require[i];
    }
    fin >> g;
    for (int i = 0; i < g; ++i) {
        for (int j = 0; j < v; ++j) {
            fin >> value[i][j];
        }
    }

    int min_count = 0xFFFFFF;
    int min_iterate = 0xFFFFFF;

    // iterate select or not select
    // 00000 ~ 11111  (g=5)
    int snapshot[1000];
    for (int it = (1 << g) - 1; it >= 0; --it) {
        for (int i = 0; i < v; ++i) {
            snapshot[i] = require[i];
        }

        int idx = 0;
        int cp = it;
        int count = 0;
        while (cp > 0) {
            if ((cp & 1) == 1) {  // use
                count++;
                for (int i = 0; i < v; ++i) {
                    snapshot[i] -= value[idx][i];
                }
            }
            cp = cp >> 1;
            idx = idx + 1;
        }

        bool flag = false;
        for (int i = 0; i < v; ++i) {
            if (snapshot[i] > 0) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            if (count < min_count) {
                min_count = count;
                min_iterate = it;
            } else if (count == min_count) {
                if (it < min_iterate) {
                    min_iterate = it;
                }
            }
        }
    }

    fout << min_count;

    int idx = 1;
    int cp = min_iterate;
    while (cp > 0) {
        if ((cp & 1) == 1) {
            fout << " " << idx;
        }
        cp = cp >> 1;
        idx = idx + 1;
    }

    fout << endl;

    return 0;
}