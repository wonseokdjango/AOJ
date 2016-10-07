#include <cstdio>
#include <cstring>
#include <queue>
#include <limits>
#include <algorithm>

#define MAXN 12
#define MAXM 100

using namespace std;

int N, M;
int WIN[MAXN];

int CNT;
int FLOW[MAXN + MAXM + 2][MAXN + MAXM + 2];
int CAPA[MAXN + MAXM + 2][MAXN + MAXM + 2];

int mf (int numWin) {

    // initialize.
    memset(FLOW, 0, sizeof(int) * (MAXN + MAXM + 2) * (MAXN + MAXM + 2));

    // go.
    for (int i = 0; i < N; ++i) {
        CAPA[i + M + 2][1] = (i == 0)? numWin - WIN[i] : numWin - WIN[i] - 1;
        if (CAPA[i + M + 2][1] < 0)
            return -1;
    }

    int ret = 0;

    while (true) {

        queue<int> q;
        vector<int> prev(N + M + 2, -1);

        q.push(0);
        prev[0] = 0;

        while (!q.empty()) {

            int here = q.front();
            q.pop();

            for (int i = 0; i < N + M + 2; ++i) {

                int flow = FLOW[here][i];
                int capa = CAPA[here][i];

                if (prev[i] == -1 && capa - flow > 0) {
                    q.push(i);
                    prev[i] = here;
                }
            }
        }

        if (prev[1] == -1)
            break;

        int cur;
        int minFlow = numeric_limits<int>::max();

        cur = 1;
        while (prev[cur] != cur) {
            minFlow = min(minFlow, CAPA[prev[cur]][cur] - FLOW[prev[cur]][cur]);
            cur = prev[cur];
        }

        ret += minFlow;

        cur = 1;
        while (prev[cur] != cur) {
            FLOW[prev[cur]][cur] += minFlow;
            FLOW[cur][prev[cur]] -= minFlow;
            cur = prev[cur];
        }
    }

    return ret;
}


int main (void) {

    int tc;
    scanf("%d", &tc);

    while (tc--) {

        // initialize.
        CNT = 0;
        memset(FLOW, 0, sizeof(int) * (MAXN + MAXM + 2) * (MAXN + MAXM + 2));
        memset(CAPA, 0, sizeof(int) * (MAXN + MAXM + 2) * (MAXN + MAXM + 2));

        // input and make graph.
        scanf("%d%d", &N, &M);

        for (int i = 0; i < N; ++i)
            scanf("%d", &WIN[i]);

        for (int i = 0; i < M; ++i) {

            int p1, p2;
            scanf("%d%d", &p1, &p2);

            if (p1 == 0 || p2 == 0)
                ++CNT;

            CAPA[0][i + 2] = 1;
            CAPA[i + 2][p1 + M + 2] = 1;
            CAPA[i + 2][p2 + M + 2] = 1;
        }

        // solve.
        int numWin;
        for (numWin = WIN[0]; numWin <= WIN[0] + CNT; ++numWin) {

            if (mf(numWin) == M)
                break;
        }

        numWin = (numWin <= WIN[0] + CNT)? numWin : -1;
        printf("%d\n", numWin);
    }

    return 0;
}
