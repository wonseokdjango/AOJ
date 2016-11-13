#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <list>

#define CANUYES_DBG
#define MAXH 20
#define MAXW 20

using namespace std;

const int dh[4] = {-1, 0, 1, 0};
const int dw[4] = {0, 1, 0, -1};

int  H, W;
char CAMP[MAXH][MAXW];
int  CAPA[MAXH * MAXW + 2][MAXH * MAXW + 2];
int  FLOW[MAXH * MAXW + 2][MAXH * MAXW + 2];

bool safe (int i, int j) {
    
    return (0 <= i && i < H && 0 <= j && j < W);
}

int mcmf (void) {

    int src = 0, sink = 1;
    int ret = 0, prev[MAXH * MAXW + 2];

    while (true) {

        queue<int> q;
        fill(prev, prev + (MAXH * MAXW + 2), -1);

        q.push(src);
        prev[src] = -2;
        while (!q.empty()) {
            int here = q.front();
            q.pop();

            for (int i = 0; i < H * W + 2; ++i) {
                if (prev[i] == -1 && CAPA[here][i] - FLOW[here][i] > 0) {
                    prev[i] = here;
                    q.push(i);
                }
            }
        }

        if (prev[sink] == -1)
            break;

        int here = sink;
        int flow = MAXH * MAXW + 2;

        while (prev[here] != -2) {
            flow = min(flow, CAPA[prev[here]][here] - FLOW[prev[here]][here]);
            here = prev[here];
        }

        ret += flow;
        here = sink;

        while (prev[here] != -2) {
            FLOW[prev[here]][here] += flow;
            FLOW[here][prev[here]] -= flow;
            here = prev[here];
        }
    }

    return ret;
}

unsigned int install (void) {

    int  pairs[MAXH * MAXW];
    bool hasPairs[MAXH * MAXW];

    fill(pairs, pairs + MAXH * MAXW, -1);
    fill(hasPairs, hasPairs + MAXH * MAXW, false);

    mcmf();

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {

            if (CAMP[i][j] != '.' || (i + j) % 2)
                continue;

            for (int dir = 0; dir < 4; ++dir) {
                int _i = i + dh[dir];
                int _j = j + dw[dir];
                int u =  i * W +  j;
                int v = _i * W + _j;

                if (safe(_i, _j) && FLOW[u + 2][v + 2] != 0) {
                    pairs[u] = v;
                    pairs[v] = u;
                    hasPairs[u] = true;
                    hasPairs[v] = true;
                    break;
                }
            }
        }
    }

    list<int> part0;    ///< initialized with A.
    list<int> part1;    ///< initialized with B - M.
    list<int>::iterator it0, it1, target;
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {

            if (CAMP[i][j] != '.')
                continue;

            int v = i * W + j;
            if ((i + j) % 2 == 0)
                part0.push_back(v);
            else if (!hasPairs[v])
                part1.push_back(v);
        }
    }

#ifndef CANUYES_DBG
    cout << "A : ";
    for (it0 = part0.begin(); it0 != part0.end(); ++it0)
        cout << *it0 << " ";
    cout << endl;
    cout << "B - M : ";
    for (it1 = part1.begin(); it1 != part1.end(); ++it1)
        cout << *it1 << " ";
    cout << endl;
#endif

    while (true) {

        target = part0.end();
        for (it0 = part0.begin(); it0 != part0.end(); ++it0) {
            
            if (target != part0.end())
                break;
            
            for (it1 = part1.begin(); it1 != part1.end(); ++it1) {

                if (CAPA[(*it0) + 2][(*it1) + 2]) {
                    target = it0;
                    break;
                }
            }
        }

        if (target == part0.end())
            break;
        
        part1.push_back(pairs[*target]);
        part0.erase(target);
    }

    for (it0 = part0.begin(); it0 != part0.end(); ++it0)
        CAMP[(*it0) / W][(*it0) % W] = '^';
    for (it1 = part1.begin(); it1 != part1.end(); ++it1)
        CAMP[(*it1) / W][(*it1) % W] = '^';
    
    return part0.size() + part1.size();
}

int main (void) {

    int tc;

    cin >> tc;
    while (tc--) {

        // initialize.
        memset(CAPA, 0, sizeof(int) * (MAXH * MAXW + 2) * (MAXH * MAXW + 2));
        memset(FLOW, 0, sizeof(int) * (MAXH * MAXW + 2) * (MAXH * MAXW + 2));

        // input.
        cin >> H >> W;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j)
                cin >> CAMP[i][j];
        }

        // make graph.
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {

                if (CAMP[i][j] != '.' || (i + j) % 2)
                    continue;

                for (int dir = 0; dir < 4; ++dir) {
                    int _i = i + dh[dir];
                    int _j = j + dw[dir];

                    if (safe(_i, _j) && CAMP[_i][_j] == '.') {
                        int u =  i * W +  j;
                        int v = _i * W + _j;
                        
                        CAPA[0][u + 2] = 1;
                        CAPA[v + 2][1] = 1;
                        CAPA[u + 2][v + 2] = 1;
                    }
                }
            }
        }

        // print answer.
        cout << install() << endl;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j)
                cout << CAMP[i][j];
            cout << endl;
        }
    }

    return 0;
}
