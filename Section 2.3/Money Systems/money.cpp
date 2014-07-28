/*
 ID: vistasw2
 PROG: money
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("money.in");
    fout.open("money.out");

    int v, n;
    fin >> v >> n;

    // remove duplicate values
    vector<int> units;
    set<int> uexists;
    for (int i = 0; i < v; ++i) {
        int t; fin >> t;
        if (uexists.find(t) == uexists.end()) {
            uexists.insert(t);
            units.push_back(t);
        }
    }
    sort(units.begin(), units.end());
    // re-calculate currency kinds
    v = units.size();

    // f[i][j]: 使用前i种货币可以构成j钱的方案数
    long long f[27][10001] = {{0}};

    for (int t = units[0]; t <= n; t += units[0]) {
        f[1][t] = 1;
    }

    for (int j = 1; j <= n; ++j) {
        for (int i = 2; i <= v; ++i) {
            for (int t = 0; units[i - 1] * t < j; ++t) {
                f[i][j] += f[i-1][j-units[i-1]*t];
            }
            if (j % units[i - 1] == 0) {
                f[i][j]++;
            }
        }
    }

    fout << f[v][n] << endl;

    return 0;
}