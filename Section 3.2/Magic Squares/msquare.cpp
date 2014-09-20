/*
 ID: vistasw2
 PROG: msquare
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

ifstream fin;
ofstream fout;

struct step
{
    char lastOp;
    string op;
    unsigned int state;
};

unsigned int state = 0x12345678;
unsigned int stateFinal = 0;

// for debug
inline void printState(unsigned int s)
{
    cout << ((s & 0xF0000000) >> 28) << " " << ((s & 0x0F000000) >> 24) << " " << ((s & 0x00F00000) >> 20) << " " << ((s & 0x000F0000) >> 16) << endl;
    cout << ((s & 0x0000000F) >>  0) << " " << ((s & 0x000000F0) >>  4) << " " << ((s & 0x00000F00) >>  8) << " " << ((s & 0x0000F000) >> 12) << endl;
}

inline unsigned int transform(unsigned int s, char op)
{
    switch (op) {
        case 'A':
            return ((s & 0xF0000000) >> 28) | ((s & 0x0F000000) >> 20) | ((s & 0x00F00000) >> 12) | ((s & 0x000F0000) >> 4) |
                   ((s & 0x0000000F) << 28) | ((s & 0x000000F0) << 20) | ((s & 0x00000F00) << 12) | ((s & 0x0000F000) << 4);
        case 'B':
            return ((s & 0x000F0000) << 12) | ((s & 0xFFF00000) >> 4) | ((s & 0x00000FFF) << 4) | ((s & 0x0000F000) >> 12);
        case 'C':
            return (s & 0xF00FF00F) | ((s & 0x000000F0) << 20) | ((s & 0x0F000000) >> 4) | ((s & 0x00000F00) >> 4) | ((s & 0x00F00000) >> 12);
        default:
            return s;
    }
}

queue<step> q;
set<unsigned int> singleton;

int main()
{
    fin.open("msquare.in");
    fout.open("msquare.out");

    unsigned int st[8];
    for (int i = 0; i < 8; ++i) {
        fin >> st[i];
    }
    stateFinal = st[0] << 28 | st[1] << 24 | st[2] << 20 | st[3] << 16 | st[4] << 12 | st[5] << 8 | st[6] << 4 | st[7];

    if (stateFinal == state) {
        fout << "0" << endl << endl;
        return 0;
    }

    q.push({'Z', "", state});

    while (q.size() > 0) {
        auto st = q.front();
        q.pop();

        if (st.state == stateFinal) {
            fout << st.op.size() << endl << st.op << endl;
            return 0;
        }

        if (singleton.find(st.state) != singleton.end()) {
            continue;
        }
        singleton.insert(st.state);

        for (char op = 'A'; op <= 'C'; ++op) {
            q.push({op, st.op + op, transform(st.state, op)});
        }
    }

    return 0;
}