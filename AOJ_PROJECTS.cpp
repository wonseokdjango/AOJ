#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

#define CANUYES_DBG

#define MAXN 100
#define MAXM 100
#define INF  100000000

using namespace std;

int N, M;
int flow[MAXN + MAXM + 2][MAXN + MAXM + 2];
int capa[MAXN + MAXM + 2][MAXN + MAXM + 2];

int mcmf (void) {

    int ret = 0;
    int src = 0, sink = 1;
    int prev[MAXN + MAXM + 2];

#ifndef CANUYES_DBG
    printf("func init\n");
#endif

    while (true) {
        
#ifndef CANUYES_DBG
        printf("outer loop\n");
#endif  
        
        queue<int> q;
        fill(prev, prev + N + M + 2, -1);

        q.push(src);
        prev[src] = -INF;
        while (!q.empty()) {
            
#ifndef CANUYES_DBG
            printf("inner loop\n");
#endif
            
            int here = q.front();
            q.pop();
            
            for (int i = 0; i < N + M + 2; ++i) {
                if (prev[i] == -1 && capa[here][i] - flow[here][i] > 0) {
                    prev[i] = here;
                    q.push(i);
                }
            }
        }

        if (prev[sink] == -1)
            break;

        int here = sink;
        int localFlow = INF;
        while (prev[here] != -INF) {

#ifndef CANUYES_DBG
            printf("track 1\n");
#endif
            
            localFlow = min(localFlow, capa[prev[here]][here] - flow[prev[here]][here]);
            here = prev[here];
        }
        
        ret += localFlow;

        here = sink;
        while (prev[here] != -INF) {

#ifndef CANUYES_DBG
            printf("track 2\n");
#endif

            flow[prev[here]][here] += localFlow;
            flow[here][prev[here]] -= localFlow;
            here = prev[here];
        }
    }

#ifndef CANUYES_DBG
    printf("func exit\n");
#endif

    return ret;
}

int main (void) {

    int tc, tmp, accum;

    scanf(" %d", &tc);
    while (tc--) {
        
        accum = 0;
        memset(flow, 0, sizeof(int) * (MAXN + MAXM + 2) * (MAXN + MAXM + 2));
        memset(capa, 0, sizeof(int) * (MAXN + MAXM + 2) * (MAXN + MAXM + 2));
        
        scanf(" %d %d", &N, &M);
        for (int i = 0; i < N; ++i) {
            scanf(" %d", &tmp);
            accum += tmp;
            capa[0][i + 2] = tmp;
        }
        for (int i = 0; i < M; ++i) {
            scanf(" %d", &tmp);
            capa[i + N + 2][1] = tmp;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                scanf(" %d", &tmp);
                if (tmp)
                    capa[i + 2][j + N + 2] = INF;
            }
        }

        printf("%d\n", accum - mcmf());
    }

    return 0;
}
