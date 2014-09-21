/*
 ID: vistasw2
 PROG: fence
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin;
ofstream fout;

int f;
vector<int> g[501];

int vertexCount;

vector<int> path;

int visit;
bool bfs_v[501];

void visitVertex(int v)
{
    visit++;
    bfs_v[v] = true;

    for (int v2 : g[v]) {
        if (v2 != -1 && !bfs_v[v2]) {
            visitVertex(v2);
        }
    }
}

bool testGraph(int v)
{
    for (int i = 1; i <= 500; ++i) {
        bfs_v[i] = false;
    }
    visit = 0;
    visitVertex(v);
    return visit == vertexCount;
}

bool selectVertex(int p)
{
    path.push_back(p);

    if (path.size() == f + 1) {
        return true;
    }

    for (int i = 0; i < g[p].size(); ++i) {
        int q = g[p][i];

        if (q != -1) {
            // delete <p,q> and <q,p>
            int j;
            g[p][i] = -1;
            for (j = 0; j < g[q].size(); ++j) {
                if (g[q][j] == p) {
                    g[q][j] = -1;
                    break;
                }
            }

            // update remaining vertex counter
            bool pSingle = true;
            for (int v : g[p]) {
                if (v != -1) {
                    pSingle = false;
                    break;
                }
            }

            if (pSingle) vertexCount--;

            if (testGraph(q)) {
                if (selectVertex(q)) {
                    return true;
                }
            }

            if (pSingle) vertexCount++;

            g[p][i] = q;
            g[q][j] = p;
        }
    }

    path.pop_back();
    return false;
}

int main()
{
    fin.open("fence.in");
    fout.open("fence.out");

    fin >> f;

    for (int i = 0; i < f; ++i) {
        int a, b; fin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // count vertex
    
    for (int i = 1; i <= 500; ++i) {
        if (g[i].size() > 0) {
            // make sure from small to large
            sort(g[i].begin(), g[i].end());
            vertexCount++;
        }
    }

    // calculate start vertex
    
    int startVertex;

    for (int i = 1; i <= 500; ++i) {
        if (g[i].size() > 0) {
            startVertex = i;
            break;
        }
    }

    for (int i = 1; i <= 500; ++i) {
        if ((g[i].size() & 1) == 1) {
            startVertex = i;
            break;
        }
    }

    selectVertex(startVertex);

    for (int v : path) {
        fout << v << endl;
    }

    return 0;
}