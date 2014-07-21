/*
ID: vistasw2
PROG: gift1
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

typedef struct {
    int initial;
    int final;
} people;

int main()
{
    ifstream fin("gift1.in");
    ofstream fout("gift1.out");

    int NP;
    fin >> NP;

    map<string, people> data;
    vector<string> names;

    for (int i = 0; i < NP; ++i) {
        string name;
        fin >> name;
        names.push_back(name);

        people p = {0, 0};
        data[name] = p;
    }

    while (fin.good()) {
        string name;
        fin >> name;

        int initial, n;
        fin >> initial >> n;

        data[name].initial = initial;
        data[name].final += initial;

        if (n > 0) {
            int single = initial / n;

            for (int i = 0; i < n; ++i) {
                string rname;
                fin >> rname;

                data[name].final -= single;
                data[rname].final += single;
            }
        }
    }

    for (string name : names) {
        fout << name << " " << data[name].final - data[name].initial << endl;
    }

    return 0;
}