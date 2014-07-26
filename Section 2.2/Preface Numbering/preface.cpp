/*
 ID: vistasw2
 PROG: preface
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

ifstream fin;
ofstream fout;

map<int, int> counting;

map<char, int> roman2int;
map<int, char> int2roman;

string mapping[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM", "", "", "", "", "", ""}
};

string getRomanFormat(int n)
{
    string ret = "";
    int pos = 0;
    while (n > 0) {
        int p = n % 10;
        n = n / 10;
        ret = mapping[pos][p] + ret;
        pos++;
    }
    return ret;
}

void count(string r)
{
    for (char c : r) {
        if (counting.find(roman2int[c]) == counting.end()) {
            counting[roman2int[c]] = 1;
        } else {
            counting[roman2int[c]]++;
        }
    }
}

int main()
{
    fin.open("preface.in");
    fout.open("preface.out");

    // for sorting convenience
    char seq[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    for (int i = 0; i < 7; ++i) {
        roman2int[seq[i]] = i;
        int2roman[i] = seq[i];
    }

    int n;
    fin >> n;

    for (int i = 1; i <= n; ++i) {
        count(getRomanFormat(i));
    }
    
    for (pair<char, int> p : counting) {
        fout << int2roman[p.first] << " " << p.second << endl;
    }

    return 0;
}