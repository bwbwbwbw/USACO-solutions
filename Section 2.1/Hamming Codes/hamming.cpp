/*
 ID: vistasw2
 PROG: hamming
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

inline int getHammingDistance(int a, int b)
{
    int c = a ^ b;
    int count = 0;

    while (c > 0) {
        if ((c & 1) == 1) {
            count++;
        }
        c = c >> 1;
    }

    return count;
}

int main()
{
    fin.open("hamming.in");
    fout.open("hamming.out");
    
    int n, b, d;
    fin >> n >> b >> d;

    int last_v;
    vector<int> v;

    v.push_back(0);
    last_v = 0;

    while (v.size() < n) {
        for (int i = last_v + 1, dest = (1 << b) - 1; i <= dest; ++i) {
            bool flag = false;
            for (int n : v) {
                if (getHammingDistance(n, i) < d) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                v.push_back(i);
                last_v = i;
                break;
            }
        }
    }

    for (int i = 0; i < v.size(); ++i) {
        fout << v[i];
        if ((i+1) % 10 == 0) {
            fout << endl;
        } else {
            if (i == v.size() - 1) {
                fout << endl;
            } else {
                fout << " ";
            }
        }
    }

    return 0;
}