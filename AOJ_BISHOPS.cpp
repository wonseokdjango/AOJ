#include <cstdio>
#include <cstring>
#include <iostream>

#include <queue>
#include <string>
#include <vector>
#include <algorithm>

#define CANUYES_DBG

#define MAXN 8

using namespace std;

int N;
vector<string> BOARD(MAXN, "");

int CAPA[2 * MAXN * MAXN + 2][2 * MAXN * MAXN + 2];
int FLOW[2 * MAXN * MAXN + 2][2 * MAXN * MAXN + 2];

bool safe (int r, int c) {

    return (0 <= r && r < N && 0 <= c && c < N && BOARD[r][c] == '.');
}

int makeGraph (void) {

    int cnt0 = 0, cnt1 = 0;
    int id[2][MAXN][MAXN] = {0, };

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            if (BOARD[i][j] == '*')
                continue;

            if (!id[0][i][j]) {
                id[0][i][j] = ++cnt0;
                for (int d = 1; d < N; ++d) {
                    if (!safe(i + d, j - d))
                        break;
                    id[0][i + d][j - d] = id[0][i][j];
                }
            }

            if (!id[1][i][j]) {
                id[1][i][j] = ++cnt1;
                for (int d = 1; d < N; ++d) {
                    if (!safe(i + d, j + d))
                        break;
                    id[1][i + d][j + d] = id[1][i][j];
                }
            }
        }
    }

#ifndef CANUYES_DBG
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("(%d, %d)   ", id[0][i][j], id[1][i][j]);
        }
        printf("\n");
    }
#endif

    memset(CAPA, 0, sizeof(int) * (2 * MAXN * MAXN + 2) * (2 * MAXN * MAXN + 2));
    memset(FLOW, 0, sizeof(int) * (2 * MAXN * MAXN + 2) * (2 * MAXN * MAXN + 2));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {

            if (BOARD[i][j] == '*')
                continue;

            int u = 2 + id[0][i][j] - 1;
            int v = 2 + cnt0 + id[1][i][j] - 1;
            CAPA[0][u] = 1;
            CAPA[u][v] = 1;
            CAPA[v][1] = 1;
        }
    }

#ifndef CANUYES_DBG
    for (int i = 0; i < 2 + cnt0 + cnt1; ++i) {
        for (int j = 0; j < 2 + cnt0 + cnt1; ++j) {
            printf("%d ", CAPA[i][j]);
        }
        printf("\n");
    }
#endif

    return 2 + cnt0 + cnt1;
}

int mcmf (int size) {

    int ret = 0;
    int src = 0, sink = 1;
    int prev[2 * MAXN * MAXN];

    while (true) {

        queue<int> q;
        fill(prev, prev + 2 * MAXN * MAXN, -1);

        q.push(src);
        prev[src] = -2;
        while (!q.empty()) {
            int here = q.front();
            q.pop();

            for (int i = 0; i < size; ++i) {
                if (prev[i] == -1 && CAPA[here][i] - FLOW[here][i] > 0) {
                    prev[i] = here;
                    q.push(i);
                }
            }
        }

        if (prev[sink] == -1)
            break;

        int here = sink;
        int minFlow = size + 1;
        while (prev[here] != -2) {
            minFlow = min(minFlow, CAPA[prev[here]][here] - FLOW[prev[here]][here]);
            here = prev[here];
        }

        here = sink;
        while (prev[here] != -2) {
            FLOW[prev[here]][here] += minFlow;
            FLOW[here][prev[here]] -= minFlow;
            here = prev[here];
        }

        ret += minFlow;
    }

    return ret;
}

int main (void) {

    int tc;
    
    cin >> tc;
    while (tc--) {
        cin >> N;
        for (int i = 0; i < N; ++i)
            cin >> BOARD[i];

        cout << mcmf(makeGraph()) << endl;
    }

    return 0;
}
