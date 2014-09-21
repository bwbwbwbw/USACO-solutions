/*
 ID: vistasw2
 PROG: shopping
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

ifstream fin;
ofstream fout;

struct pack
{
    int n;
    vector<int> c;
    vector<int> k;
    int p;
};

int main()
{
    fin.open("shopping.in");
    fout.open("shopping.out");

    map<int, int> idMap;
    int idCount = 0;

    int req[5];

    int prom[105][5];
    int promPrice[105];
    int promCount = 0;

    vector<pack> packs;
    int s; fin >> s;
    for (int i = 0; i < s; ++i) {
        pack p;
        fin >> p.n;
        for (int j = 0; j < p.n; ++j) {
            int c, k; fin >> c >> k;
            p.c.push_back(c);
            p.k.push_back(k);
        }
        fin >> p.p;
        packs.push_back(p);
    }

    // store original price
    int b; fin >> b;
    int org[5] = {0};
    for (int i = 0; i < b; ++i) {
        int c, k, p;
        fin >> c >> k >> p;
        if (idMap.find(c) == idMap.end()) {
            idMap[c] = idCount++;
        }

        req[idMap[c]] = k;
        org[idMap[c]] = p;
    }

    // prepare promotion
    for (pack p : packs) {
        fill_n(prom[promCount], 5, 0);
        for (int i = 0; i < p.n; ++i) {
            prom[promCount][idMap[p.c[i]]] = p.k[i];
        }
        promPrice[promCount] = p.p;
        promCount++;
    }

    // calculate!

    int f[6][6][6][6][6];
    f[0][0][0][0][0] = 0;

    // f[x0][x1][x2][x3][x4]
    // 买 x0 件物品1，x1 件物品2，…… 的最小花费
    for (int x0 = 0; x0 <= req[0]; ++x0) {
    for (int x1 = 0; x1 <= req[1]; ++x1) {
    for (int x2 = 0; x2 <= req[2]; ++x2) {
    for (int x3 = 0; x3 <= req[3]; ++x3) {
    for (int x4 = 0; x4 <= req[4]; ++x4) {
        f[x0][x1][x2][x3][x4] = org[0]*x0 + org[1]*x1 + org[2]*x2 + org[3]*x3 + org[4]*x4;

        for (int p = 0; p < promCount; p++) {
            int t0 = max(x0 - prom[p][0], 0);
            int t1 = max(x1 - prom[p][1], 0);
            int t2 = max(x2 - prom[p][2], 0);
            int t3 = max(x3 - prom[p][3], 0);
            int t4 = max(x4 - prom[p][4], 0);
            if (f[t0][t1][t2][t3][t4] + promPrice[p] < f[x0][x1][x2][x3][x4]) {
                f[x0][x1][x2][x3][x4] = f[t0][t1][t2][t3][t4] + promPrice[p];
            }
            //cout << x0 << " " << x1 << " " << x2 << " " << x3 << " " << x4 << "=" << f[x0][x1][x2][x3][x4] << endl;
        }
    }
    }
    }
    }
    }

    fout << f[req[0]][req[1]][req[2]][req[3]][req[4]] << endl;

    return 0;
}