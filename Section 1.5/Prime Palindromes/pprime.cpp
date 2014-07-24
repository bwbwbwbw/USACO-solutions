/*
ID: vistasw2
PROG: pprime
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

int a, b;
vector<int> primes;

bool isPrime(int num)
{
    if (num <= 1) {
        return false;
    }

    if ((num & 1) == 0) {
        return false;
    }

    int max_test = sqrt(num);

    for (int p : primes) {
        if (p > max_test) {
            break;
        }
        if (num % p == 0) {
            return false;
        }
    }

    return true;
}

int getNumberLength(int num)
{
    if (num <= 1) {
        return 1;
    }
    return floor(log10(num)) + 1;
}

int reverseNumber(int number)
{
    int ret = 0;

    while (number > 0) {
        ret = ret * 10 + number % 10;
        number /= 10;
    }

    return ret;
}

int pow10(int n)
{
    return pow(10, (float)n);
}

void generatePalindromeLengthN(int length)
{
    if (length == 1) {
        for (int final = 2; final <= 9; ++final) {
            if (final < a || final > b) continue;
            if (isPrime(final)) {
                fout << final << endl;
            }
        }
        return;
    }

    int l = length / 2;

    int start = pow10(l - 1);
    int end = pow10(l) - 1;

    if (length % 2 == 1) {
        int k1 = pow10(l + 1);
        int k2 = pow10(l);
        for (int i = start; i <= end; ++i) {
            for (int mid = 0; mid <= 9; ++mid) {
                int final = i * k1 + mid * k2 + reverseNumber(i);
                if (final < a || final > b) continue;
                if (isPrime(final)) {
                    fout << final << endl;
                }
            }
        }
    } else {
        int k1 = pow10(l);
        for (int i = start; i <= end; ++i) {
            int final = i * k1 + reverseNumber(i);
            if (final < a || final > b) continue;
            if (isPrime(final)) {
                fout << final << endl;
            }
        }
    }
}

void generatePrimeTable()
{
    char hit[10001] = {0};
    hit[0] = 1;
    hit[1] = 1;

    for (int i = 2; i <= 5000; ++i) {
        if (hit[i] == 0) {
            for (int j = i * 2; j <= 10000; j += i) {
                hit[j] = 1;
            }
        }
    }

    for (int i = 2; i <= 10000; ++i) {
        if (hit[i] == 0) {
            primes.push_back(i);
        }
    }
}

int main()
{
    fin.open("pprime.in");
    fout.open("pprime.out");

    generatePrimeTable();
    fin >> a >> b;

    int lA = getNumberLength(a);
    int lB = getNumberLength(b);

    for (int i = lA; i <= lB; ++i) {
        generatePalindromeLengthN(i);
    }

    return 0;
}