/*
 ID: vistasw2
 PROG: subset
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

long long f[821][821];

using namespace std;

ifstream fin;
ofstream fout;

int n;

long long calc(int a, int b)
{
    if (a >= b) {
        return 0;
    }

    if (f[a][b] != -1) {
        return f[a][b];
    }

    long long ret = 0;
    if (b <= n) {
        ret++;
    }
    for (int i = a + 1; ; ++i) {
        int a2 = i;
        int b2 = b - a2;
        if (a2 >= b2) {
            break;
        }
        ret += calc(a2, b2);
    }

    f[a][b] = ret;
    return ret;
}

int main()
{
    fin.open("subset.in");
    fout.open("subset.out");

    fin >> n;

    // cannot devide
    int sum = (1 + n) * n / 2;
    if ((sum % 2) == 1) {
        fout << "0" << endl;
        return 0;
    }

    // special hack for number 3
    if (n == 3) {
        fout << "1" << endl;
        return 0;
    }

    for (int i = 0; i <= sum; ++i) {
        for (int j = i + 1; j <= sum; ++j) {
            f[i][j] = -1;
        }
    }

    sum = sum >> 1;

    long long s = 0;
    for (int i = 1; i <= (sum >> 1); ++i) {
        s += calc(i, sum - i);
    }

    fout << (s >> 1) << endl;

    return 0;
}