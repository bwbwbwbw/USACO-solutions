/*
 ID: vistasw2
 PROG: lamps
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("lamps.in");
    fout.open("lamps.out");

    int n, c;
    fin >> n >> c;
    
    vector<int> enl;
    vector<int> not_enl;

    while (true) {
        int d;
        fin >> d;
        if (d == -1) {
            break;
        } else {
            enl.push_back(d);
        }
    }

    while (true) {
        int d;
        fin >> d;
        if (d == -1) {
            break;
        } else {
            not_enl.push_back(d);
        }
    }

    bool lights[101];
    set<string> result;

    for (int state = 0; state <= ((1 << 4) - 1); ++state) {
        int t[4] = {state & 1, (state >> 1 & 1), (state >> 2 & 1), (state >> 3 & 1)};
        int s = t[0] + t[1] + t[2] + t[3];
        if ((c - s) % 2 != 0 || (s > c)) {
            continue;
        }

        // reset lighte
        for (int i = 1; i <= n; ++i) {
            lights[i] = true;
        }

        // transform
        if (t[0] == 1) {
            for (int i = 1; i <= n; ++i) {
                lights[i] = !lights[i];
            }
        }
        if (t[1] == 1) {
            for (int i = 1; i <= n; i += 2) {
                lights[i] = !lights[i];
            }
        }
        if (t[2] == 1) {
            for (int i = 2; i <= n; i += 2) {
                lights[i] = !lights[i];
            }
        }
        if (t[3] == 1) {
            for (int i = 1; i <= n; i += 3) {
                lights[i] = !lights[i];
            }
        }

        // test condition
        bool flag = true;
        for (int id : enl) {
            if (lights[id] != true) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;

        for (int id : not_enl) {
            if (lights[id] != false) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;

        // put result
        
        string str_state = "";
        str_state.reserve(n);
        for (int i = 1; i <= n; ++i) {
            if (lights[i]) {
                str_state += "1";
            } else {
                str_state += "0";
            }
        }

        result.insert(str_state);
    }

    if (result.size() == 0) {
        fout << "IMPOSSIBLE" << endl;
    } else {
        for (string state : result) {
            fout << state << endl;
        }
    }

    return 0;
}