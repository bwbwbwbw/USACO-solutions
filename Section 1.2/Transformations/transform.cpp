/*
ID: vistasw2
PROG: transform
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int n;

string rotate90(string map)
{
    char *ret = new char[map.size() + 1];
    ret[map.size()] = '\0';

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int index_src = i * n + j;
            int index_dest = j * n + (n - i) - 1;
            ret[index_dest] = map[index_src];
        }
    }

    string r(ret);
    delete[] ret;

    return r;
}

string rotate180(string map)
{
    return rotate90(rotate90(map));
}

string rotate270(string map)
{
    return rotate90(rotate90(rotate90(map)));
}

string reflect(string map)
{
    char *ret = new char[map.size() + 1];
    ret[map.size()] = '\0';

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int index_src = i * n + j;
            int index_dest = i * n + (n - j) - 1;
            ret[index_dest] = map[index_src];
        }
    }

    string r(ret);
    delete[] ret;

    return r;
}

int main()
{
    ifstream fin("transform.in");
    ofstream fout("transform.out");

    fin >> n;

    string original = "";
    for (int i = 0; i < n; ++i) {
        string line;
        fin >> line;
        original += line;
    }

    string final = "";
    for (int i = 0; i < n; ++i) {
        string line;
        fin >> line;
        final += line;
    }
    
    if (rotate90(original) == final) {
        fout << "1" << endl;
        return 0;
    }

    if (rotate180(original) == final) {
        fout << "2" << endl;
        return 0;
    }

    if (rotate270(original) == final) {
        fout << "3" << endl;
        return 0;
    }

    if (reflect(original) == final) {
        fout << "4" << endl;
        return 0;
    }

    if (rotate90(reflect(original)) == final ||
        rotate180(reflect(original)) == final ||
        rotate270(reflect(original)) == final) {
        fout << "5" << endl;
        return 0;
    }

    if (original == final) {
        fout << "6" << endl;
        return 0;
    }

    fout << "7" << endl;
    return 0;
}