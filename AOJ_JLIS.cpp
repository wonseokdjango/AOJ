#include <cstdio>
#include <limits>

#define MAXLEN 101
#define MAX_UPDATE(A, B) ( (A) = ( ( (A) > (B) ) ? (A) : (B) ) )

const long long MAXNUM = std::numeric_limits<long long>::max();

int C;
int N, M;
long long A[MAXLEN];
long long B[MAXLEN];
int CACHE[MAXLEN][MAXLEN];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        // input.
        scanf(" %d %d", &N, &M);
        for (int a = 0; a < N; ++a)
            scanf(" %lld", &A[a]);
        for (int b = 0; b < M; ++b)
            scanf(" %lld", &B[b]);
        
        // padding.
        A[N] = B[M] = MAXNUM;

        for (int i = N - 1; i >= 0; --i)
        {
            CACHE[i][M] = 1;
            for (int ni = i + 1; ni < N; ++ni)
            {
                if (A[i] < A[ni])
                    MAX_UPDATE(CACHE[i][M], 1 + CACHE[ni][M]);
            }
        }
        for (int j = M - 1; j >= 0; --j)
        {
            CACHE[N][j] = 1;
            for (int nj = j + 1; nj < M; ++nj)
            {
                if (B[j] < B[nj])
                    MAX_UPDATE(CACHE[N][j], 1 + CACHE[N][nj]);
            }
        }
        CACHE[N][M] = 0;
        
        // solve.
        for (int i = N - 1; i >= 0; --i)
        {
            for (int j = M - 1; j >= 0; --j)
            {
                CACHE[i][j] = (A[i] == B[j]) ? 1 : 2;
                if (A[i] < B[j])
                {
                    for (int ni = i + 1; ni <= N; ++ni)
                    {
                        if (A[i] < A[ni])
                            MAX_UPDATE(CACHE[i][j], 1 + CACHE[ni][j]);
                    }
                }
                else if (A[i] > B[j])
                {
                    for (int nj = j + 1; nj <= M; ++nj)
                    {
                        if (B[j] < B[nj])
                            MAX_UPDATE(CACHE[i][j], 1 + CACHE[i][nj]);
                    }
                }
                else
                {
                    for (int ni = i + 1; ni <= N; ++ni)
                    {
                        for (int nj = j + 1; nj <= M; ++nj)
                        {
                            if (A[i] < A[ni] && B[j] < B[nj])
                                MAX_UPDATE(CACHE[i][j], 1 + CACHE[ni][nj]);
                        }
                    }
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
                MAX_UPDATE(ans, CACHE[i][j]);
        }

        // answer.
        printf("%d\n", ans);
    }

    return 0;
}
