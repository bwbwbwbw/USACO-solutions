/*
ID: vistasw2
PROG: crypt1
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int result = 0;

int n;
vector<int> data;
map<int, bool> m;
int eq[5] = {0};

// check whether a number is given in input
bool isValid(int number)
{
    return m.find(number) != m.end();
}

/*

          012  v1
    x      34
   ----------
          ***  r1
         ***   r2
   ----------
         ****  r3
         
 */

void testEquation()
{
    int v1 = eq[0] * 100 + eq[1] * 10 + eq[2];
    int r1 = v1 * eq[4];
    if (r1 > 999) return;
    int r2 = v1 * eq[3];
    if (r2 > 999) return;
    if (!isValid(r1 % 10)) return;
    if (!isValid((r1 / 10) % 10)) return;
    if (!isValid((r1 / 100) % 10)) return;
    if (!isValid(r2 % 10)) return;
    if (!isValid((r2 / 10) % 10)) return;
    if (!isValid((r2 / 100) % 10)) return;
    int r3 = r1 + r2 * 10;
    if (r3 > 9999) return;
    if (!isValid(r3 % 10)) return;
    if (!isValid((r3 / 10) % 10)) return;
    if (!isValid((r3 / 100) % 10)) return;
    if (!isValid((r3 / 1000) % 10)) return;

    result++;
}

void search(int digit) {
    if (digit >= 5) {
        testEquation();
        return;
    }
    for (int i = 0; i < n; ++i) {
        eq[digit] = data[i];
        search(digit + 1);
    }
}

int main()
{
    ifstream fin("crypt1.in");
    ofstream fout("crypt1.out");

    fin >> n;
    data.reserve(n);

    for (int i = 0; i < n; ++i) {
        int d;
        fin >> d;
        data.push_back(d);
        m[d] = true;
    }

    search(0);

    fout << result << endl;

    return 0;
}