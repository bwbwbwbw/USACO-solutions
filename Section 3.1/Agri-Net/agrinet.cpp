/*
 ID: vistasw2
 PROG: agrinet
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

int g[101][101];

int main()
{
    fin.open("agrinet.in");
    fout.open("agrinet.out");

    int n;
    fin >> n;

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            fin >> g[row][col];
        }
    }

    int v0 = 0;
    int ans = 0;
    int closestDis[101], closestPoint[101];

    for (int i = 0; i < n; ++i) {
        closestDis[i] = g[i][v0];
        closestPoint[i] = v0;
    }

    for (int i = 0; i < n - 1; ++i) {
        int minDis = 0xFFFFFF;
        int minPoint;
        for (int j = 0; j < n; ++j) {
            if (closestDis[j] > 0 && closestDis[j] < minDis) {
                minDis = closestDis[j];
                minPoint = j;
            }
        }
        ans += minDis;
        closestDis[minPoint] = 0;
        for (int j = 0; j < n; ++j) {
            if (g[j][minPoint] < closestDis[j]) {
                closestDis[j] = g[j][minPoint];
                closestPoint[j] = minPoint;
            }
        }
    }

    fout << ans << endl;

    return 0;
}