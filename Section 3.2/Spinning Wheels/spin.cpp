/*
 ID: vistasw2
 PROG: spin
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

ifstream fin;
ofstream fout;

const int WHEEL_COUNT = 5;

struct wheel
{
    int v;
    int w;
    int start_angle[5];
    int width[5];
};

int main()
{
    fin.open("spin.in");
    fout.open("spin.out");

    wheel wheels[WHEEL_COUNT];

    for (int i = 0; i < WHEEL_COUNT; ++i) {
        fin >> wheels[i].v;
        fin >> wheels[i].w;
        for (int j = 0; j < wheels[i].w; ++j) {
            fin >> wheels[i].start_angle[j];
            fin >> wheels[i].width[j];
        }
    }

    int t = 0;
    int fill[360];

    for (int p = 0; p < 360; ++p) {
        fill_n(fill, 360, 0);
        for (int i = 0; i < WHEEL_COUNT; ++i) {
            int startOffset = t * wheels[i].v;
            for (int j = 0; j < wheels[i].w; ++j) {
                //cout << t << " " << i << " " << j << ": " << startOffset + wheels[i].start_angle[j] << " - " <<  startOffset + wheels[i].start_angle[j] + wheels[i].width[j] << endl;
                for (int k = startOffset + wheels[i].start_angle[j]; k <= startOffset + wheels[i].start_angle[j] + wheels[i].width[j]; ++k) {
                    if (++fill[k % 360] == WHEEL_COUNT) {
                        fout << t << endl;
                        return 0;
                    }
                }
            }
        }
        t++;
    }

    fout << "none" << endl;
    return 0;
}