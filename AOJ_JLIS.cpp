#include <cstdio>
#include <limits>

#define MAXLEN 100
#define MAXVAL(A, B) ( ( (A) > (B) ) ? (A) : (B) )

int C;
int N, M;
unsigned int A[MAXLEN + 1], B[MAXLEN + 1];
unsigned int CACHE[MAXLEN + 1][MAXLEN + 1];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        // input.
        scanf(" %d %d", &N, &M);
        for (int a = 0; a < N; ++a)
            scanf(" %d", &A[a]);
        for (int b = 0; b < M; ++b)
            scanf(" %d", &B[b]);
        A[N] = std::numeric_limits<int>::max() + 1;
        B[M] = std::numeric_limits<int>::max() + 1;

        // solve.
        for (int i = N - 1; i >= 0; --i)
        {
            CACHE[i][M] = 1;
            for (int ni = i + 1; ni < N; ++ni)
            {
                if (A[i] < A[ni])
                    CACHE[i][M] = MAXVAL(CACHE[i][M], 1 + CACHE[ni][M]);
            }
        }
        for (int j = M - 1; j >= 0; --j)
        {
            CACHE[N][j] = 1;
            for (int nj = j + 1; nj < M; ++nj)
            {
                if (B[j] < B[nj])
                    CACHE[N][j] = MAXVAL(CACHE[N][j], 1 + CACHE[N][nj]);
            }
        }
        CACHE[N][M] = 0;
/*
        for (int i = 0; i < N; ++i)
            printf("%5d", CACHE[i][M]);
        printf("\n");

        for (int j = 0; j < M; ++j)
            printf("%5d", CACHE[N][j]);
        printf("\n");
*/
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
                            CACHE[i][j] = MAXVAL(CACHE[i][j], 1 + CACHE[ni][j]);
                    }
                }
                else if (A[i] > B[j])
                {
                    for (int nj = j + 1; nj <= M; ++nj)
                    {
                        if (B[j] < B[nj])
                            CACHE[i][j] = MAXVAL(CACHE[i][j], 1 + CACHE[i][nj]);
                    }
                }
                else
                {
                    for (int ni = i + 1; ni <= N; ++ni)
                    {
                        for (int nj = j + 1; nj <= M; ++nj)
                        {
                            if (A[i] < A[ni] && B[j] < B[nj])
                                CACHE[i][j] = MAXVAL(CACHE[i][j], 1 + CACHE[ni][nj]);
                        }
                    }
                }
            }
        }

        unsigned int ans = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                //printf("%5d", CACHE[i][j]);
                ans = MAXVAL(ans, CACHE[i][j]);
            }
        }

        // answer.
        printf("%d\n", ans);
    }

    return 0;
}
