/*
ID: vistasw2
PROG: milk
LANG: C++11
*/
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct ask
{
    int price;
    int amount;
};

bool cmp(const ask& a, const ask& b)
{
    return a.price < b.price;
}

int main()
{
    ifstream fin("milk.in");
    ofstream fout("milk.out");

    int n, m;
    fin >> n >> m;

    vector<ask> list;
    list.reserve(m);

    for (int i = 0; i < m; ++i) {
        int p, a;
        fin >> p >> a;

        ask item = {p, a};
        list.push_back(item);
    }

    sort(list.begin(), list.end(), cmp);

    int cur_cost = 0, cur_amount = 0;
    for (int i = 0; i < list.size(); ++i) {
        if (cur_amount + list[i].amount <= n) {
            cur_amount += list[i].amount;
            cur_cost += list[i].amount * list[i].price;
        } else {
            int delta = n - cur_amount;
            cur_amount = n;
            cur_cost += delta * list[i].price;
            break;
        }
    }

    fout << cur_cost << endl;

    return 0;
}