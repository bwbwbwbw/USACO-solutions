/*
 ID: vistasw2
 PROG: sort3
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("sort3.in");
    fout.open("sort3.out");
    
    vector<int> d;
    int n; fin >> n;
    for (int i = 0; i < n; ++i) {
        int num; fin >> num;
        d.push_back(num);
    }

    vector<int> sorted = d;
    sort(sorted.begin(), sorted.end());

    int times = 0;
    int index = 0;

    for (int i = 0; i < n; ++i) {
        if (sorted[i] != d[i]) {
            for (int j = i + 1; j < n; ++j) {
                if (d[j] == sorted[i] && sorted[j] == d[i]) {
                    times++;
                    swap(d[i], d[j]);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (sorted[i] != d[i] && d[i] == 1) {
            times += 2;
        }
    }    

    fout << times << endl;

    return 0;
}