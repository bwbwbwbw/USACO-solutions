/*
 ID: vistasw2
 PROG: butter
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin;
ofstream fout;

const int INFINITE = 0xFFFFFF;

int minDistance = INFINITE;

int n, p, c;
int cows[500];
vector<int> vt[801];
int g[801][801];

int dist[801];
bool inQueue[801];

void SPFA(int source)
{
    queue<int> q;

    for (int i = 1; i <= p; ++i) {
        dist[i] = INFINITE;
        inQueue[i] = false;
    }
    dist[source] = 0;

    inQueue[source] = true;
    q.push(source);

    while (q.size() > 0) {
        int p = q.front();
        q.pop();
        inQueue[p] = false;
        for (int p2 : vt[p]) {
            if (g[p][p2] > 0 && dist[p] + g[p][p2] < dist[p2]) {
                dist[p2] = dist[p] + g[p][p2];
                if (!inQueue[p2]) {
                    q.push(p2);
                    inQueue[p2] = true;
                }
            }
        }
    }

    int distance = 0;
    for (int cow = 0; cow < n; ++cow) {
        distance += dist[cows[cow]];
    }
    if (distance < minDistance) {
        minDistance = distance;
    }
}

int main()
{
    fin.open("butter.in");
    fout.open("butter.out");

    fin >> n >> p >> c;

    for (int i = 0; i < n; ++i) {
        fin >> cows[i];
    }

    for (int i = 0; i < c; ++i) {
        int a, b, c;
        fin >> a >> b >> c;

        vt[a].push_back(b);
        vt[b].push_back(a);
        g[a][b] = c;
        g[b][a] = c;
    }

    for (int i = 1; i <= p; ++i) {
        SPFA(i);
    }

    fout << minDistance << endl;

    return 0;
}