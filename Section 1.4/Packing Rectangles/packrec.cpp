/*
ID: vistasw2
PROG: packrec
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct rectangle
{
    int w;
    int h;
};

rectangle rec[4];
int v[4] = {0};
int s[4] = {0};
int rev[4] = {0};

int min_area = 0xFFFFFF;
vector<rectangle> result;

int max(int a, int b)
{
    return std::max(a, b);
}

int max(int a, int b, int c)
{
    return max(max(a, b), c);
}

int max(int a, int b, int c, int d)
{
    return max(max(a, b, c), d);
}

void test(int width, int height, int c)
{
    if (width > height) {
        swap(width, height);
    }
    if (width * height <= min_area) {
        min_area = width * height;
        rectangle rec = {width, height};
        result.push_back(rec);
    }
}

void tryRectangle()
{
    // case 1
    test(
        rec[s[0]].w + rec[s[1]].w + rec[s[2]].w + rec[s[3]].w, 
        max(rec[s[0]].h, rec[s[1]].h, rec[s[2]].h, rec[s[3]].h),
        1
    );

    // case 2
    test(
        max(rec[s[0]].w + rec[s[1]].w + rec[s[2]].w, rec[s[3]].w),
        max(rec[s[0]].h, rec[s[1]].h, rec[s[2]].h) + rec[s[3]].h,
        2
    );

    // case 3
    test(
        max(rec[s[0]].w + rec[s[1]].w, rec[s[2]].w) + rec[s[3]].w,
        max(rec[s[3]].h, max(rec[s[0]].h, rec[s[1]].h) + rec[s[2]].h),
        3
    );

    // case 4
    test(
        rec[s[0]].w + max(rec[s[1]].w, rec[s[2]].w) + rec[s[3]].w,
        max(rec[s[0]].h, rec[s[1]].h + rec[s[2]].h, rec[s[3]].h),
        4
    );

    // case 5
    test(
        max(rec[s[0]].w, rec[s[1]].w) + rec[s[2]].w + rec[s[3]].w,
        max(rec[s[0]].h + rec[s[1]].h, rec[s[2]].h, rec[s[3]].h),
        5
    );

    // case 6
    if (rec[s[3]].h >= rec[s[1]].h && rec[s[0]].w <= rec[s[1]].w) {
        test(
            max(rec[s[0]].w + rec[s[2]].w, rec[s[1]].w + rec[s[3]].w),
            max(rec[s[2]].h + rec[s[3]].h, rec[s[0]].h + rec[s[1]].h),
            6
        );
    }
}

void search(int pos)
{
    if (pos >= 4) {
        tryRectangle();
        return;
    }

    for (int i = 0; i < 4; ++i) {
        if (v[i] == 0) {
            s[pos] = i;
            v[i] = 1;
            search(pos + 1);
            v[i] = 0;
        }
    }
}

bool cmp(const rectangle& a, const rectangle& b)
{
    if (a.w != b.w) {
        return a.w < b.w;
    } else {
        return a.h < b.h;
    }
}

int main()
{
    ifstream fin("packrec.in");
    ofstream fout("packrec.out");

    for (int i = 0; i < 4; ++i) {
        fin >> rec[i].w >> rec[i].h;
    }

    // reverse width & height?
    // 0000b - 1111b
    for (int i = 0; i < 16; ++i) {
        v[0] = v[1] = v[2] = 0;
        rev[0] = i & 1;
        rev[1] = (i >> 1) & 1;
        rev[2] = (i >> 2) & 1;
        rev[3] = (i >> 3) & 1;
        for (int j = 0; j < 4; ++j) {
            if (rev[j] == 1) swap(rec[j].w, rec[j].h);
        }
        search(0);
        for (int j = 0; j < 4; ++j) {
            if (rev[j] == 1) swap(rec[j].w, rec[j].h);
        }
    }

    map<int, bool> singleton;

    sort(result.begin(), result.end(), cmp);

    // find min solution
    fout << min_area << endl;
    for (rectangle rec : result) {
        if (rec.w * rec.h == min_area) {
            if (singleton.find(rec.w) == singleton.end()) {
                singleton[rec.w] = true;
                fout << rec.w << " " << rec.h << endl;
            }
        }
    }

    return 0;
}