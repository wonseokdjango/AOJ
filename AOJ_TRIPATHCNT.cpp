#include <cstdio>
#include <cstring>

#define MAXN 101

int C;
int N;
int TRIANGLE[MAXN][MAXN];

int PATHSUM[MAXN][MAXN];
int PATHCNT[MAXN][MAXN];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        scanf(" %d", &N);
        for (int h = 0; h < N; ++h)
        {
            for (int pos = 0; pos < h + 1; ++pos)
                scanf(" %d", &TRIANGLE[h][pos]);
        }

        // initialize.
        memset(PATHSUM, 0, sizeof(int) * MAXN * MAXN);
        memset(PATHCNT, 0, sizeof(int) * MAXN * MAXN);
        for (int pos = 0; pos < N; ++pos)
        {
            PATHSUM[N - 1][pos] = TRIANGLE[N - 1][pos];
            PATHCNT[N - 1][pos] = 1;
        }

        // solve.
        for (int h = N - 2; h >= 0; --h)
        {
            for (int pos = 0; pos < h + 1; ++pos)
            {
                if (PATHSUM[h + 1][pos] > PATHSUM[h + 1][pos + 1])
                {
                    PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos];
                    PATHCNT[h][pos] = PATHCNT[h + 1][pos];
                }
                else if (PATHSUM[h + 1][pos] < PATHSUM[h + 1][pos + 1])
                {
                    PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos + 1];
                    PATHCNT[h][pos] = PATHCNT[h + 1][pos + 1];
                }
                else
                {
                    PATHSUM[h][pos] = TRIANGLE[h][pos] + PATHSUM[h + 1][pos];
                    PATHCNT[h][pos] = PATHCNT[h + 1][pos] + PATHCNT[h + 1][pos + 1];
                }
            }
        }

        printf("%d\n", PATHCNT[0][0]);
    }

    return 0;
}
