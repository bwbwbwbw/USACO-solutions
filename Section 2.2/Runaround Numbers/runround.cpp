/*
 ID: vistasw2
 PROG: runround
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin;
ofstream fout;

bool found = false;
int foundNumber = -1;

int digits[9] = {0};
int mindig[9] = {0};

bool used[10] = {false};

bool isRoundNumber(int maxLength)
{
    bool visited[10] = {false};

    int idx = 0;

    for (int n = 0; n < maxLength; ++n) {
        idx = (idx + digits[idx]) % maxLength;
        visited[idx] = true;
    }

    for (int i = 0; i < maxLength; ++i) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

// search no-repeat numbers larger than min
void searchIn(int maxLength, int pos, bool compare)
{
    if (found) {
        return;
    }

    if (pos >= maxLength) {
        // equal to mindig: ignore
        if (compare && digits[pos] == mindig[pos]) {
            return;
        }
        if (isRoundNumber(maxLength)) {
            found = true;
            foundNumber = 0;
            for (int i = 0; i < maxLength; ++i) {
                foundNumber = foundNumber * 10 + digits[i];
            }
            return;
        }
    }

    for (int i = 1; i <= 9; ++i) {
        if (found) {
            return;
        }
        if (!used[i]) {
            if (compare && i < mindig[pos]) {
                continue;
            }

            used[i] = true;
            digits[pos] = i;
            bool nextCompare;
            if (!compare) {
                nextCompare = false;
            } else if (digits[pos] == mindig[pos]) {
                nextCompare = true;
            } else  {
                nextCompare = false;
            }

            searchIn(maxLength, pos + 1, nextCompare);

            used[i] = false;
        }
    }
}

int main()
{
    fin.open("runround.in");
    fout.open("runround.out");

    int min; fin >> min;
    int index = 0, indexMax = floor(log10(min)) + 1;
    while (min > 0) {
        mindig[indexMax - index - 1] = min % 10;
        min = min / 10;
        index++;
    }

    searchIn(index, 0, true);
    if (!found) {
        for (int i = index + 1; i <= 9; ++i) {
            searchIn(i, 0, false);
        }
    }

    fout << foundNumber << endl;

    return 0;
} 