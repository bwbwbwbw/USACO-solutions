/*
 ID: vistasw2
 PROG: zerosum
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

const int OP_PLUS = 1;
const int OP_MINUS = 2;
const int OP_APPEND = 0;

int n;
int opcode[10] = {0};

void test()
{
    int result = 0;
    int last_ops = 0;
    int last_sig = 1;

    for (int i = 1; i <= n - 1; ++i) {
        last_ops = last_ops * 10 + i;
        switch(opcode[i]) {
            case OP_PLUS:
                result += last_ops * last_sig;
                last_ops = 0;
                last_sig = 1;
                break;
            case OP_MINUS:
                result += last_ops * last_sig;
                last_ops = 0;
                last_sig = -1;
                break;
            case OP_APPEND:
                break;
        }
    }
    last_ops = last_ops * 10 + n;
    result += last_ops * last_sig;

    if (result != 0) return;

    for (int i = 1; i <= n - 1; ++i) {
        fout << i;
        switch(opcode[i]) {
            case OP_PLUS:
                fout << "+";
                break;
            case OP_MINUS:
                fout << "-";
                break;
            case OP_APPEND:
                fout << " ";
                break;
        }
    }
    fout << n << endl;
}

void search(int pos)
{
    if (pos >= n) {
        test();
        return;
    }

    for (int i = 0; i < 3; ++i) {
        opcode[pos] = i;
        search(pos + 1);
    }
}

int main()
{
    fin.open("zerosum.in");
    fout.open("zerosum.out");

    fin >> n;
    search(1);

    return 0;
}