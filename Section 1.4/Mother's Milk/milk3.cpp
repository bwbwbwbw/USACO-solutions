/*
ID: vistasw2
PROG: milk3
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

struct status
{
    char a;
    char b;
    char c;
};

inline bool operator<(const status& lhs, const status& rhs)
{
    if (lhs.a != rhs.a) {
        return lhs.a < rhs.a;
    } else if (lhs.b != rhs.b) {
        return lhs.b < rhs.b;
    } else {
        return lhs.c < rhs.c;
    }
}

status volume;
status current;

set<int> answer;
set<status> singleton;

/*
    opcode:

    1:  C -> A
    2:  C -> B
    3:  A -> B
    4:  A -> C
    5:  B -> A
    6:  B -> C
 */
bool operate(int opcode)
{
    int v, delta;

    if (opcode == 1) {
        if (current.c == 0) return false;
        if (current.a == volume.a) return false;
        v = current.a + current.c;
        if (v <= volume.a) {
            current.a = v;
            current.c = 0;
        } else {
            delta = volume.a - current.a;
            current.a = volume.a;
            current.c -= delta;
        }
    } else if (opcode == 2) {
        if (current.c == 0) return false;
        if (current.b == volume.b) return false;
        v = current.b + current.c;
        if (v <= volume.b) {
            current.b = v;
            current.c = 0;
        } else {
            delta = volume.b - current.b;
            current.b = volume.b;
            current.c -= delta;
        }
    } else if (opcode == 3) {
        if (current.a == 0) return false;
        if (current.b == volume.b) return false;
        v = current.b + current.a;
        if (v <= volume.b) {
            current.b = v;
            current.a = 0;
        } else {
            delta = volume.b - current.b;
            current.b = volume.b;
            current.a -= delta;
        }
    } else if (opcode == 4) {
        if (current.a == 0) return false;
        if (current.c == volume.c) return false;
        v = current.c + current.a;
        if (v <= volume.c) {
            current.c = v;
            current.a = 0;
        } else {
            delta = volume.c - current.c;
            current.c = volume.c;
            current.a -= delta;
        }
    } else if (opcode == 5) {
        if (current.b == 0) return false;
        if (current.a == volume.a) return false;
        v = current.a + current.b;
        if (v <= volume.a) {
            current.a = v;
            current.b = 0;
        } else {
            delta = volume.a - current.a;
            current.a = volume.a;
            current.b -= delta;
        }
    } else if (opcode == 6) {
        if (current.b == 0) return false;
        if (current.c == volume.c) return false;
        v = current.c + current.b;
        if (v <= volume.c) {
            current.c = v;
            current.b = 0;
        } else {
            delta = volume.c - current.c;
            current.c = volume.c;
            current.b -= delta;
        }
    }

    return true;
}

void search()
{
    status snapshot = current;
    for (int i = 1; i <= 6; ++i) {
        operate(i);
        if (singleton.find(current) == singleton.end()) {
            singleton.insert(current);
            if (current.a == 0) {
                answer.insert((int)current.c);
            }
            search();
        }
        current = snapshot;
    }
}

int main()
{
    ifstream fin("milk3.in");
    ofstream fout("milk3.out");

    int a, b, c;
    fin >> a >> b >> c;
    volume.a = (char)a;
    volume.b = (char)b;
    volume.c = (char)c;
    current.a = 0;
    current.b = 0;
    current.c = volume.c;
    
    answer.insert((int)current.c);
    singleton.insert(current);

    search();

    int flag = true;
    for (int ans : answer) {
        if (flag) {
            flag = false;
            fout << ans;
        } else {
            fout << " " << ans;
        }
    }
    fout << endl;

    return 0;
}