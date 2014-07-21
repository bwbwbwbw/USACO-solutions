/*
ID: vistasw2
PROG: ride
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("ride.in");
    ofstream fout("ride.out");

    string comet, group;
    fin >> comet;
    fin >> group;

    int comet_number = 1, group_number = 1;

    for (char c : comet) {
        comet_number *= int(c - 'A') + 1;
    }
    for (char c : group) {
        group_number *= int(c - 'A') + 1;
    }

    if (comet_number % 47 == group_number % 47) {
        fout << "GO" << endl;
    } else {
        fout << "STAY" << endl;
    }

    return 0;
}