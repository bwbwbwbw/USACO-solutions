/*
ID: vistasw2
PROG: palsquare
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int b;

char mapping[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'
};

string toBaseN(int n)
{
    string ret = "";
    while (n > 0) {
        ret += mapping[n % b];
        n /= b;
    }

    return string(ret.rbegin(), ret.rend());
}

bool isPalindromic(string s)
{
    string s2(s.rbegin(), s.rend());
    return s2 == s;
}

int main()
{
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");

    fin >> b;

    for (int n = 1; n <= 300; ++n) {
        string f = toBaseN(n * n);
        if (isPalindromic(f)) {
            fout << toBaseN(n) << " " << f << endl;
        }
    }

    return 0;
}