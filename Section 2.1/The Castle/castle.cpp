/*
 ID: vistasw2
 PROG: castle
 LANG: C++11
 */
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

ifstream fin;
ofstream fout;

int w, h, n;

vector<int> gfill;
vector<int> rsize;
vector<vector<int>> g;

int fillSize, maxFillSize = 0;

inline int getGraphIndex(int row, int col)
{
    return row * w + col;
}

void fillGraph(int index, int color)
{
    if (gfill[index] != 0) {
        return;
    }
    
    queue<int> q;
    q.push(index);
    
    while (q.size() > 0) {
        int node = q.front();
        q.pop();
        if (gfill[node] != 0) {
            continue;
        }
        
        gfill[node] = color;
        fillSize++;

        for (int node2 : g[node]) {
            if (gfill[node2] == 0) {
                q.push(node2);
            }
        }
    }
}

int main()
{
    fin.open("castle.in");
    fout.open("castle.out");
    
    fin >> w >> h;
    n = w * h;

    gfill = vector<int>(n + 2, 0);
    rsize = vector<int>(n + 2, 0);
    g.resize(n);
    
    for (int row = 0; row < h; ++row) {
        for (int col = 0; col < w; ++col) {
            int v; fin >> v;
            // 1 1 1 1
            // s e n w
            if ((v & 1) == 0) {
                // no wall at west
                g[getGraphIndex(row,col)].push_back(getGraphIndex(row,col-1));
                g[getGraphIndex(row,col-1)].push_back(getGraphIndex(row,col));
            }
            v = v >> 1;
            if ((v & 1) == 0) {
                // no wall at north
                g[getGraphIndex(row,col)].push_back(getGraphIndex(row-1,col));
                g[getGraphIndex(row-1,col)].push_back(getGraphIndex(row,col));
            }
        }
    }
    
    // 1. count and max
    int fillIndex = 1;
    for (int i = 0; i < n; ++i) {
        if (gfill[i] == 0) {
            fillSize = 0;
            fillGraph(i, fillIndex);
            rsize[fillIndex] = fillSize;
            if (fillSize > maxFillSize) {
                maxFillSize = fillSize;
            }
            fillIndex++;
        }
    }
    
    int roomCount = fillIndex - 1;
    
    fout << roomCount << endl;
    fout << maxFillSize << endl;
    
    int maxCombineSize = 0, maxCombineRow = -1, maxCombineCol = -1;
    string maxCombineDirection = "";
    
    // 2. try connect
    for (int col = 0; col < w; ++col) {
        for (int row = h - 1; row >= 0; --row) {
            // remove north
            if (row > 0) {
                int p1 = getGraphIndex(row, col), p2 = getGraphIndex(row-1, col);
                if (gfill[p1] != gfill[p2]) {
                    if (rsize[gfill[p1]] + rsize[gfill[p2]] > maxCombineSize) {
                        maxCombineSize = rsize[gfill[p1]] + rsize[gfill[p2]];
                        maxCombineRow = row;
                        maxCombineCol = col;
                        maxCombineDirection = "N";
                    }
                }
            }
            // remove east
            if (col < w - 1) {
                int p1 = getGraphIndex(row, col), p2 = getGraphIndex(row, col+1);
                if (gfill[p1] != gfill[p2]) {
                    if (rsize[gfill[p1]] + rsize[gfill[p2]] > maxCombineSize) {
                        maxCombineSize = rsize[gfill[p1]] + rsize[gfill[p2]];
                        maxCombineRow = row;
                        maxCombineCol = col;
                        maxCombineDirection = "E";
                    }
                }
            }
        }
    }
    
    fout << maxCombineSize << endl;
    fout << maxCombineRow + 1 << " " << maxCombineCol + 1 << " " << maxCombineDirection << endl;
    
    return 0;
}