/*
ID: vistasw2
PROG: ariprog
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct result
{
    int a;
    int b;
};

bool cmp(const result& a, const result& b)
{
    if (a.b != b.b) {
        return a.b < b.b;
    } else {
        return a.a < b.a;
    }
}

int main()
{
    ifstream fin("ariprog.in");
    ofstream fout("ariprog.out");

    int n, m;
    fin >> n >> m;

    int map[125001] = {0};
    set<int> collection;

    for (int p = 0; p <= m; ++p) {
        for (int q = 0; q <= m; ++q) {
            collection.insert(p*p + q*q);
        }
    }

    // generate delta
    int last = 0;
    for (int element : collection) {
        map[last] = element - last;
        last = element;
    }
    map[0] = 1;
    map[last] = 1;

    // iterate b and a
    int size_max = m * m * 2;
    vector<result> ret;

    for (int a : collection) {
        //a + b * (n - 1) <= size_max
        //b <= (size_max - a) / (n - 1)
        for (int b = map[a], sz = (size_max - a) / (n - 1) + 1; b <= sz; ++b) {
            int cur = a;
            bool flag = false;
            // check all elements
            for (int i = 1; i < n; ++i) {
                cur += b;
                if (map[cur] == 0) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                result r = {a, b};
                ret.push_back(r);
            }
        }
    }

    if (ret.size() == 0) {
        fout << "NONE" << endl;
    } else {
        sort(ret.begin(), ret.end(), cmp);
        for (result& r : ret) {
            fout << r.a << " " << r.b << endl;
        }
    }

    return 0;
}