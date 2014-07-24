/*
ID: vistasw2
PROG: checker
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

int n;
int map[13][13];
int rowUsed[13] = {0};
int coord1Used[27] = {0};
int coord2Used[27] = {0};
int seq[13] = {0};

int ret = 0;

inline int getCoordIndex1(int i, int j)
{
    return (i + j);
}

inline int getCoordIndex2(int i, int j)
{
    return (n - i - 1) + j;
}

void search(int index)
{
    if (index >= n) {
        ret++;
        if (ret <= 3) {
            for (int i = 0; i < n - 1; ++i) {
                fout << seq[i] + 1 << " ";
            }
            fout << seq[n -1] + 1 << endl;
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (rowUsed[i] == 1) continue;
        int coord1 = getCoordIndex1(index, i);
        if (coord1Used[coord1] == 1) continue;
        int coord2 = getCoordIndex2(index, i);
        if (coord2Used[coord2] == 1) continue;

        coord1Used[coord1] = 1;
        coord2Used[coord2] = 1;
        rowUsed[i] = 1;
        seq[index] = i;

        search(index + 1);
        
        rowUsed[i] = 0;
        coord1Used[coord1] = 0;
        coord2Used[coord2] = 0;
    }
}

int main()
{
    fin.open("checker.in");
    fout.open("checker.out");

    fin >> n;
    search(0);
    fout << ret << endl;
    
    return 0;
}