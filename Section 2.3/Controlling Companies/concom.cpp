/*
 ID: vistasw2
 PROG: concom
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

int g[102][102] = {{0}};
int maxN = 0;

bool visited[102];
int ct[102];

void search(int index)
{
    if (visited[index]) {
        return;
    }
    visited[index] = true;

    for (int i = 1; i <= maxN; ++i) {
        ct[i] += g[index][i];
        if (ct[i] > 50) {
            search(i);
        }
    }
}

int main()
{
    fin.open("concom.in");
    fout.open("concom.out");

    int n; fin >> n;

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        fin >> a >> b >> c;
        if (a > maxN) maxN = a;
        if (b > maxN) maxN = b;
        g[a][b] = c;
    }

    for (int i = 1; i <= maxN; ++i) {
        fill_n(visited + 1, maxN, false);
        fill_n(ct + 1, maxN, 0);
        search(i);
        for (int t = 1; t <= maxN; ++t) {
            if (ct[t] > 50 && t != i) {
                fout << i << " " << t << endl;
            }
        }
    }

    return 0;
}