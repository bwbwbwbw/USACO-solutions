/*
ID: vistasw2
PROG: dualpal
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

char mapping[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

string toBaseN(int n, int base)
{
    string ret = "";
    while (n > 0) {
        ret += mapping[n % base];
        n /= base;
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
    ifstream fin("dualpal.in");
    ofstream fout("dualpal.out");

    int n, s;
    fin >> n >> s;

    while (n > 0) {
        s++;

        int match_count = 0;
        for (int base = 2; base <= 10; ++base) {
            if (isPalindromic(toBaseN(s, base))) {
                match_count++;
                if (match_count >= 2) {
                    break;
                }
            }
        }

        if (match_count == 2) {
            n--;
            fout << s << endl;
        }
    }

    return 0;
}