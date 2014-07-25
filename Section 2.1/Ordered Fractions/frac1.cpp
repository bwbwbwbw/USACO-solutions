/*
 ID: vistasw2
 PROG: frac1
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct frac
{
    int a;
    int b;
    double value;
};

ifstream fin;
ofstream fout;

int gcd(int a, int b)
{
    int c;
    while (a != 0) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

bool cmp(const frac& a, const frac& b)
{
    return a.value < b.value;
}

int main()
{
    fin.open("frac1.in");
    fout.open("frac1.out");
    
    int n;
    fin >> n;

    vector<frac> result;

    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i <= j && gcd(i, j) == 1) {
                frac f = {i, j, (double)i / j};
                result.push_back(f);
            }
        }
    }

    sort(result.begin(), result.end(), cmp);

    for (frac& f : result) {
        fout << f.a << "/" << f.b << endl;
    }

    return 0;
}