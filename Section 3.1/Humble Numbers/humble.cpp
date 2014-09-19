/*
 ID: vistasw2
 PROG: humble
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

const unsigned int INFINITE = 0xFFFFFFFF;

int size = 0;
unsigned int last;
int k, n;

vector<unsigned int> results;
vector<unsigned int> elements;
vector<unsigned int> startIndex;

inline void expand()
{
    unsigned int min = INFINITE;
    
    for (int i = 0; i < k; ++i) {
        for (int j = startIndex[i]; j < size; ++j) {
            int next = results[j] * elements[i];
            if (next <= last) {
                continue;
            }
            if (next < min) {
                min = next;
            }
            startIndex[i] = j;
            break;
        }
    }

    results[size] = min;
    last = min;
    size++;
}

int main()
{
    fin.open("humble.in");
    fout.open("humble.out");

    fin >> k >> n;

    elements.reserve(k);
    startIndex.reserve(k);
    results.reserve(n + 1);

    for (int i = 0; i < k; ++i) {
        int e; fin >> e;
        elements.push_back(e);
        startIndex.push_back(0);
    }

    results.push_back(1);
    size = 1;
    last = 1;

    while (size <= n) {
        expand();
    }

    fout << results[n] << endl;

    return 0;
}