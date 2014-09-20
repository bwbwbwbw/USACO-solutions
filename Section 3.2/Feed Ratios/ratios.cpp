/*
 ID: vistasw2
 PROG: ratios
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin;
ofstream fout;

int main()
{
    fin.open("ratios.in");
    fout.open("ratios.out");

    int a1, b1, c1, d1;
    int a2, b2, c2, d2;
    int a3, b3, c3, d3;

    fin >> d1 >> d2 >> d3;
    fin >> a1 >> a2 >> a3;
    fin >> b1 >> b2 >> b3;
    fin >> c1 >> c2 >> c3;

    int dtr = a1*b2*c3+b1*c2*a3+c1*a2*b3 - (c1*b2*a3+a1*c2*b3+a2*b1*c3);
    if (dtr == 0) {
        fout << "NONE" << endl;
        return 0;
    }

    int a = b2*c3-c2*b3;
    int b = c1*b3-b1*c3;
    int c = b1*c2-c1*b2;
    int d = c2*a3-a2*c3;
    int e = a1*c3-c1*a3;
    int f = c1*a2-a1*c2;
    int g = a2*b3-b2*a3;
    int h = b1*a3-a1*b3;
    int i = a1*b2-b1*a2;

    double x = double(d1*a + d2*b + d3*c) / dtr;
    double y = double(d1*d + d2*e + d3*f) / dtr;
    double z = double(d1*g + d2*h + d3*i) / dtr;

    if (x < 0 || y < 0 || z < 0) {
        fout << "NONE" << endl;
        return 0;
    }

    int k = 1;
    while (true) {
        if (x * k == floor(x * k) && y * k == floor(y * k) && z * k == floor(z * k)) {
            break;
        } else {
            k++;
        }
    }

    fout << int(x * k) << " " << int(y * k) << " " << int(z * k) << " " << k << endl;

    return 0;
}