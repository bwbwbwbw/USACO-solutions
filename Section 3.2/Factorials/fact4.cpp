/*
 ID: vistasw2
 PROG: fact4
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
    fin.open("fact4.in");
    fout.open("fact4.out");

    int n; long long result = 1;
    fin >> n;

    for (int i = 2; i <= n; ++i) {
        result = result * i;
        while (result % 10 == 0) {
            result /= 10;
        }
        result = result % 1000000;
    }

    fout << result % 10 << endl;

    return 0;
}