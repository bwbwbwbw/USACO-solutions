/*
ID: vistasw2
PROG: milk2
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main()
{
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");

    int n;
    fin >> n;

    vector<int> t_start, t_end;
    t_start.reserve(n);
    t_end.reserve(n);

    set<int> t_seq;

    for (int i = 0; i < n; ++i) {
        int a, b;
        fin >> a >> b;
        t_start.push_back(a);
        t_end.push_back(b);
        t_seq.insert(a);
        t_seq.insert(b);
    }

    if (n == 1) {
        fout << t_end[0] - t_start[0] << " " << 0 << endl;
        return 0;
    }

    // serialize input
    map<int, int> t_map, t_map_rev; 
    int index = 0;
    
    // t_seq is already sorted
    for (auto it = t_seq.begin(); it != t_seq.end(); ++it) {
        t_map[*it] = index;
        t_map_rev[index] = *it;
        index++;
    }

    int m = t_seq.size() - 1;
    vector<int> colors(m, 0);

    // fill color
    for (int i = 0; i < n; ++i) {
        for (int p = t_map[t_start[i]], q = t_map[t_end[i]]; p < q; ++p) {
            colors[p] = 1;
        }
    }

    /*
    for (int i = 0; i < m; ++i) {
        cout << colors[i] << " ";
    }*/

    // first element must be 1
    int last_filled = t_map_rev[1] - t_map_rev[0];
    int last_empty = 0;

    int max_filled = last_filled;
    int max_empty = last_empty;

    for (int i = 1; i < m; ++i) {
        if (colors[i] != colors[i - 1]) {
            if (last_empty > max_empty) max_empty = last_empty;
            if (last_filled > max_filled) max_filled = last_filled;
            last_empty = 0;
            last_filled = 0;
        }

        if (colors[i] == 0) {
            last_empty += t_map_rev[i + 1] - t_map_rev[i];
        } else {
            last_filled += t_map_rev[i + 1] - t_map_rev[i];
        }
    }

    if (last_empty > max_empty) max_empty = last_empty;
    if (last_filled > max_filled) max_filled = last_filled;

    fout << max_filled << " " << max_empty << endl;

    return 0;
}