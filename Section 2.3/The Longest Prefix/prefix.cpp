/*
 ID: vistasw2
 PROG: prefix
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

int max(int a, int b)
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int main()
{
    fin.open("prefix.in");
    fout.open("prefix.out");

    vector<string> d;
    while (true) {
        string word; fin >> word;
        if (word == ".") {
            break;
        }
        d.push_back(word);
    }

    string seq;

    while (fin.good()) {
        string l;
        fin >> l;
        seq += l;
    }

    int n = seq.size();

    // f[i]: 到第i个字符为止是否可匹配
    bool f[200005] = {false};
    int result = 0;

    for (int i = 0; i <= n; ++i) {
        for (string& word : d) {
            int start = i - (int)word.size();
            if (start < 0) continue;
            if (seq.substr(start, word.size()) != word) continue;
            if (start > 0 && !f[start]) continue;

            f[i] = true;
            result = i;
            break;
        }
    }

    fout << result << endl;

    return 0;
}