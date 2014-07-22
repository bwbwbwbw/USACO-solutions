/*
ID: vistasw2
PROG: barn1
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct magic
{
    int index;
    int id;
    int delta;
};

bool cmpDelta(const magic& a, const magic& b)
{
    return a.delta > b.delta;
}

bool cmpId(const magic& a, const magic& b)
{
    return a.id < b.id;
}

int main()
{
    ifstream fin("barn1.in");
    ofstream fout("barn1.out");

    int m, s, c;
    fin >> m >> s >> c;

    if (m >= c) {
        fout << c << endl;
        return 0;
    }

    vector<magic> data;
    data.reserve(c);
    
    for (int i = 0; i < c; ++i) {
        int id;
        fin >> id;
        
        magic m;
        m.id = id;

        data.push_back(m);
    }

    // sort asc
    sort(data.begin(), data.end(), cmpId);
    int last = -1;
    for (int i = 0; i < c; ++i) {
        if (last == -1) {
            data[i].delta = -1;
        } else {
            data[i].delta = data[i].id - last;
        }
        data[i].index = i;
        last = data[i].id;
    }

    // calculate greatest N gap
    sort(data.begin(), data.end(), cmpDelta);
    vector<int> cuts;
    cuts.reserve(m + 1);

    cuts.push_back(0);
    for (int i = 0; i < m - 1; ++i) {
        cuts.push_back(data[i].index);
    }
    cuts.push_back(c);
    sort(cuts.begin(), cuts.end());

    // calculate barn length
    sort(data.begin(), data.end(), cmpId);
    int count = 0;
    for (int i = 1; i < cuts.size(); ++i) {
        count += data[cuts[i] - 1].id - data[cuts[i - 1]].id + 1;
    }

    fout << count << endl;

    return 0;
}