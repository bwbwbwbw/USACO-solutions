/*
 ID: vistasw2
 PROG: cowtour
 LANG: C++11
 */
#include <iomanip>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin;
ofstream fout;

const double INFINITE = 1e20;

int n;
int x[151], y[151];
double g[151][151];
double maxDistance[151];
double ans = INFINITE;

double getDistance(int p1, int p2)
{
    double dx = x[p1]-x[p2];
    double dy = y[p1]-y[p2];

    return sqrt(dx*dx + dy*dy);
}

int main()
{
    fin.open("cowtour.in");
    fout.open("cowtour.out");

    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> x[i] >> y[i];
    }

    fin.get();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c = fin.get();
            if (c == '1') {
                g[i][j] = getDistance(i, j);
            } else {
                g[i][j] = INFINITE;
            }
        }
        fin.get();
    }
    for (int i = 0; i < n; ++i) {
        g[i][i] = 0;
    }

    // calculate shorest path
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (g[i][k] + g[j][k] < g[i][j]) {
                    g[i][j] = g[i][k] + g[j][k];
                }
            }
        }
    }

    for (int p = 0; p < n; ++p) {
        maxDistance[p] = 0;
    }

    for (int p = 0; p < n; ++p) {
        for (int src = 0; src < n; ++src) {
            if (g[p][src] != INFINITE && g[p][src] > maxDistance[p]) {
                maxDistance[p] = g[p][src];
            }
        }
    }

    for (int p1 = 0; p1 < n; p1++) {
        for (int p2 = 0; p2 < n; p2++) {
            // select two different area
            if (g[p1][p2] != INFINITE) {
                continue;
            }

            // get max distance in area1
            double max1 = maxDistance[p1];
            double max2 = maxDistance[p2];
            double distance = max1 + max2 + getDistance(p1, p2);

            //cout << char('A' + p1) << "-" << char('A' + p2) << " " << max1 << " " << max2 << " " << distance << endl;

            if (distance < ans) {
                ans = distance;
            }
        }
    }

    for (int p = 0; p < n; ++p) {
        if (maxDistance[p] > ans) {
            ans = maxDistance[p];
        }
    }

    fout.setf(ios::fixed);
    fout << setprecision(6) << ans << endl;

    return 0;
}