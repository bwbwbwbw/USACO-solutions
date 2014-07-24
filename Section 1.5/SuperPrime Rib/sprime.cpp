/*
ID: vistasw2
PROG: sprime
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

int pow10(int n)
{
    return pow(10, (float)n);
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

int digits[8];
int n;

void fillDigit(int index, int current)
{
    if (index >= n) {
        fout << current << endl;
        return;
    }
    for (int i = 0; i <= 9; ++i) {
        digits[index] = i;
        int next = current * 10 + i;
        if (isPrime(next)) {
            fillDigit(index + 1, next);
        }
    }
}

int main()
{
    fin.open("sprime.in");
    fout.open("sprime.out");

    generatePrimeTable();

    fin >> n;

    int firstDigit[] = {2, 3, 5, 7};
    for (int i : firstDigit) {
        digits[0] = i;
        fillDigit(1, i);
    }
    
    return 0;
}