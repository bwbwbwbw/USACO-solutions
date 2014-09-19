/*
 ID: vistasw2
 PROG: inflate
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("inflate.in");
    fout.open("inflate.out");

    int m, n;
    fin >> m >> n;
    
    vector<int> c, w, f;
    c.reserve(n);
    w.reserve(n);
    f.reserve(m + 1);

    for (int i = 0; i < n; ++i) {
        int a, b;
        fin >> a >> b;
        w.push_back(a);
        c.push_back(b);
    }

    for (int i = 0; i < n; ++i) {
        for (int v = c[i]; v <= m; ++v) {
            f[v] = max(f[v], f[v-c[i]]+w[i]);
        }
    }

    fout << f[m] << endl;

    return 0;
}