/*
ID: vistasw2
PROG: calfflac
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>

using namespace std;

string line2;

int isPalindromic(int left, int right)
{
    if (right == left + 1) {
        return -1;
    }

    while (left < right) {
        if (line2[left] != line2[right - 1]) {
            return right;
        }
        left++;right--;
    }

    return -1;
}

int main()
{
    ifstream fin("calfflac.in");
    ofstream fout("calfflac.out");

    string line((std::istreambuf_iterator<char>(fin)),
                 std::istreambuf_iterator<char>());

    line2.reserve(line.size());

    map<int, int> mapping;

    // format string
    int sz = 0;
    for (int i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c >= 'a' && c <= 'z') {
            line2 += c;
            mapping[sz++] = i;
        } else if (c >= 'A' && c <= 'Z') {
            line2 += (c - 'A' + 'a');
            mapping[sz++] = i;
        }
    }

    int max_length = -1;
    int max_start = -1;
    int size = (int)line2.size();

    // 1. iterate center letter
    for (int i = 0; i < size; ++i) {
        int length = 1;
        while (true) {
            int left = i - length + 1;
            int right = i + length - 1;
            if (left < 0 || right >= size || line2[left] != line2[right]) {
                int l = i - (length - 1) + 1;
                int r = i + (length - 1) - 1;
                int len = mapping[r] - mapping[l] + 1;
                if (len > max_length) {
                    max_length = len;
                    max_start = mapping[l];
                }
                break;
            }
            length++;
        }
    }

    // 2. iterate center position
    for (int i = 1; i < size; ++i) {
        int length = 1;
        while (true) {
            int left = i - length;
            int right = i + length - 1;
            if (left < 0 || right >= size || line2[left] != line2[right]) {
                int l = i - (length - 1);
                int r = i + (length - 1) - 1;
                int len = mapping[r] - mapping[l] + 1;
                if (len > max_length) {
                    max_length = len;
                    max_start = mapping[l];
                }
                break;
            }
            length++;
        }
    }

    string final = line.substr(max_start, max_length);
    int count = 0;
    for (char c : final) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            count++;
        }
    }
    fout << count << endl;
    fout << line.substr(max_start, max_length) << endl;

    return 0;
}