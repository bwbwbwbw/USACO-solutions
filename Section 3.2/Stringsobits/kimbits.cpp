/*
 ID: vistasw2
 PROG: kimbits
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

const int MAX_TABLE_N = 32;
unsigned int C[MAX_TABLE_N + 1][MAX_TABLE_N + 1];

inline void initTable()
{
    for(int i = 0; i <= MAX_TABLE_N; ++i) {
        C[0][i] = 0;
        C[i][0] = 1;
    }
    for(int i = 1; i <= MAX_TABLE_N; ++i)
    {
        for(int j = 1; j <= MAX_TABLE_N; ++j) {
            C[i][j] = C[i-1][j] + C[i-1][j-1];
        }
    }
}

int main()
{
    fin.open("kimbits.in");
    fout.open("kimbits.out");

    initTable();

    int n, l;
    unsigned int p;

    fin >> n >> l >> p;

    // position of 11100000000000000000 = C(20,3)+C(20,2)+C(20,1)+C(20,0)
    for (int bit = 1; bit <= n; ++bit) {
        // 计算剩下位数中如果存在 l 个 1，可以有几种情况
        unsigned int sum = 0;
        for (int j = 0; j <= l; ++j) {
            sum += C[n - bit][j];
        }
        if (p > sum) {
            // 要取的个数超过了上述情况，则该位必定为1，剩下可用1个数减少
            fout << 1;
            l--;
            p -= sum;
        } else {
            // 要取的个数没超过，那么这位是0
            fout << 0;
        }
    }

    fout << endl;

    return 0;
}