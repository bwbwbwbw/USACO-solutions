/*
 ID: vistasw2
 PROG: contact
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

struct seq
{
    string sem;
    long long val;
};

long long toValue(string s)
{
    long long val = 0;
    for (char c : s) {
        if (c == '1') {
            val = (val << 1) + 1;
        } else {
            val = val << 1;
        }
    }
    return val;
}

bool sortfunc(const seq& a, const seq& b)
{
    if (a.sem.size() != b.sem.size()) {
        return a.sem.size() < b.sem.size();
    } else {
        return a.val < b.val;
    }
}

int main()
{
    fin.open("contact.in");
    fout.open("contact.out");

    int a, b, n;
    fin >> a >> b >> n;

    string str;

    while (fin.good()) {
        string line;
        getline(fin, line);
        str += line;
    }

    cout << toValue("111101011110") << " " << toValue("011001101101");

    map<string, int> counter;

    for (int i = 0; i <= str.size() - a; ++i) {
        for (int len = a; len <= b; ++len) {
            string sub = str.substr(i, len);
            if (sub.size() != len) {
                continue;
            }
            if (counter.find(sub) ==  counter.end()) {
                counter[sub] = 0;
            }
            counter[sub]++;
        }
    }

    map<int, vector<seq>> result; 

    for (pair<string, int> p : counter) {
        if (result.find(p.second) == result.end()) {
            vector<seq> r;
            result[p.second] = r;
        }
        result[p.second].push_back(seq({p.first, toValue(p.first)}));
    }

    int cResult = 0;

    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        auto p = *it;
        fout << p.first << endl;
        sort(p.second.begin(), p.second.end(), sortfunc);
        bool first = true;

        int cItem = 0;

        for (auto q : p.second) {
            if (first) {
                first = false;
            } else {
                fout << " ";
            }
            fout << q.sem;
            if (++cItem % 6 == 0) {
                fout << endl;
                first = true;
            }
        }
        if (cItem % 6 != 0) {
            fout << endl;
        }

        if (++cResult >= n) {
            break;
        }
    }

    return 0;
}