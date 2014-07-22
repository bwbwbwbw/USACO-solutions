/*
ID: vistasw2
PROG: namenum
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char mapping[26] = {
        '2', '2', '2',
        '3', '3', '3',
        '4', '4', '4',
        '5', '5', '5',
        '6', '6', '6',
        '7', '0', '7', '7',
        '8', '8', '8',
        '9', '9', '9', '0'
    };

    ifstream fin("namenum.in");
    ofstream fout("namenum.out");

    string input;
    fin >> input;

    int c = 0;

    ifstream fdict("dict.txt");
    while (fdict.good()) {
        string line;
        fdict >> line;
        if (line.size() == input.size()) {
            string s = "";
            for (char c : line) {
                s += mapping[c - 'A'];
            }
            if (s == input) {
                c++;
                fout << line << endl;
            }
        }
    }

    if (c == 0) {
        fout << "NONE" << endl;
    }

    return 0;
}