/*
ID: vistasw2
PROG: friday
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream fin("friday.in");
    ofstream fout("friday.out");

    int n;
    fin >> n;

    int count[7] = {0};
    int index = 2;

    for (int i = 0; i < n; ++i) {
        int year = 1900 + i;
        int month = 1;
        int day = 1;

        while(true) {
            if (day == 13) {
                count[index]++;
            }

            index++;
            if (index > 6) {
                index = 0;
            }

            day++;
            if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
                if (day > 31) {
                    day = 1;
                    month++;
                }
            } else if (month == 2) {
                if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
                    if (day > 29) {
                        day = 1;
                        month++;
                    }
                } else {
                    if (day > 28) {
                        day = 1;
                        month++;
                    }
                }
            } else {
                if (day > 30) {
                    day = 1;
                    month++;
                }
            }

            if (month > 12) {
                break;
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        fout << count[i] << " ";
    }
    fout << count[6] << endl;

    return 0;
}