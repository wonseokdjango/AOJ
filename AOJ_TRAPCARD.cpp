#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>

#define CANUYES_DBG
#define MAXH 20
#define MAXW 20

const int dh[4] = {-1, 0, 1, 0};
const int dw[4] = {0, 1, 0, -1};

using namespace std;

int H, W, T;
char CAMP[MAXH][MAXW];

int CAPA[MAXH * MAXW + 2][MAXH * MAXW + 2];
int FLOW[MAXH * MAXW + 2][MAXH * MAXW + 2];

bool safe (int i, int j) {

    return (0 <= i && i < H && 0 <= j && j < W);
}

int mcmf (void) {

    int ret = 0;
    int src = 0, sink = 1;
    int prev[MAXH * MAXW + 2];

    while (true) {

        queue<int> q;
        fill(prev, prev + MAXH * MAXW + 2, -1);

        q.push(src);
        prev[src] = -2;
        while (!q.empty()) {
            int here = q.front();
            q.pop();

            for (int i = 0; i < H * W + 2; ++i) {
                if (prev[i] == -1 &&
                    CAPA[here][i] - FLOW[here][i] > 0) {
                    
                    prev[i] = here;
                    q.push(i);
                }
            }
        }

        if (prev[sink] == -1)
            break;

        int cur = sink;
        int minFlow = H * W + 2;
        while (prev[cur] != -2) {
            minFlow = min(minFlow, CAPA[prev[cur]][cur] - FLOW[prev[cur]][cur]);
            cur = prev[cur];
        }

        ret += minFlow;

        cur = sink;
        while (prev[cur] != -2) {
            FLOW[prev[cur]][cur] += minFlow;
            FLOW[cur][prev[cur]] -= minFlow;
            cur = prev[cur];
        }
    }

    return ret;
}

void install (void) {

    int pairs[MAXH * MAXW];
    fill(pairs, pairs + MAXH * MAXW, -1);

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {

            if (CAMP[i][j] != '.')
                continue;

            bool matched = false;
            for (int dir = 0; dir < 4; ++dir) {
                if (safe(i + dh[dir], j + dw[dir]) &&
                    CAMP[i + dh[dir]][j + dw[dir]] == '.') {
                    
                    int u = i * W + j;
                    int v = (i + dh[dir]) * W + j + dw[dir];

                    if(FLOW[u + 2][v + 2] != 0) {
                        pairs[u] = v;
                        pairs[v] = u;
                        matched = true;
                        break;
                    }
                }
            }

            if (!matched)
                CAMP[i][j] = '^';
        }
    }

    while (true) {

        int cnt = 0;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {

                if (CAMP[i][j] != '.')
                    continue;

                int u = i * W + j;
                int v = pairs[u];
                
                if (CAMP[u / W][u % W] != '.' ||
                    CAMP[v / W][v % W] != '.')
                    continue;

                for (int dir = 0; dir < 4; ++dir) {
                    if (safe(u / W + dh[dir], u % W + dw[dir]) &&
                        CAMP[u / W + dh[dir]][u % W + dw[dir]] == '^') {

                        CAMP[v / W][v % W] = '^';
                        ++cnt;
                        break;
                    }
                }
            }
        }

        if (cnt == 0) {

            for (int i = 0; i < H; ++i) {
                for (int j = 0; j < W; ++j) {
            
                    if (CAMP[i][j] != '.')
                        continue;
            
                    int u = i * W + j;
                    int v = pairs[u];

                    if (CAMP[u / W][u % W] == '.' &&
                        CAMP[v / W][v % W] == '.') {

                        CAMP[u / W][u % W] = '^';
                        ++cnt;
                        j = i = MAXH * MAXW;
                    }
                }
            }

            if (cnt == 0)
                break;
        }
    }
}

int main (void) {

    int tc;

    cin >> tc;
    while (tc--) {

        T = 0;
        memset(CAPA, 0, sizeof(int) * (MAXH * MAXW + 2) * (MAXH * MAXW + 2));
        memset(FLOW, 0, sizeof(int) * (MAXH * MAXW + 2) * (MAXH * MAXW + 2));

        cin >> H >> W;
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cin >> CAMP[i][j];
                if (CAMP[i][j] == '.')
                    ++T;
            }
        }

#ifndef CANUYES_DBG
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cout << CAMP[i][j];
            }
            cout << endl;
        }
#endif

        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {

                if (CAMP[i][j] != '.' || (i + j) % 2)
                    continue;

                for (int dir = 0; dir < 4; ++dir) {
                    if (safe(i + dh[dir], j + dw[dir]) &&
                        CAMP[i + dh[dir]][j + dw[dir]] == '.') {
                        
                        int u = i * W + j;
                        int v = (i + dh[dir]) * W + j + dw[dir];
                        
                        CAPA[0][u + 2] = CAPA[v + 2][1] = CAPA[u + 2][v + 2] = 1;
                    }
                }
            }
        }

        cout << T - mcmf() << endl;
        
        install();
        for (int i = 0; i < H; ++i) {
            for (int j = 0; j < W; ++j) {
                cout << CAMP[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
