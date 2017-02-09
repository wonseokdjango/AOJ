#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

#define MAX_Q 10
#define MAX_N 100
#define MAX_VAL 100000001

#define MIN_UPDATE(DEST, SRC) ((DEST) = (((DEST) < (SRC)) ? (DEST) : (SRC)))

using namespace std;

int C;
int N, S;
int ARR[MAX_N + 1];

int CACHE[MAX_N + 1][MAX_Q + 1];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        scanf(" %d %d", &N, &S);
        for (int it = 0; it < N; ++it)
            scanf(" %d", &ARR[it]);

        // init.
        for (int row = 0; row < MAX_N + 1; ++row)
        {
            for (int col = 0; col < MAX_Q + 1; ++col)
                CACHE[row][col] = MAX_VAL;
        }
        for (int row = 0; row < MAX_N + 1; ++row)
            CACHE[row][0] = MAX_VAL;
        for (int col = 0; col < MAX_Q + 1; ++col)
            CACHE[N][col] = 0;

        // sort.
        sort(ARR, ARR + N);

        // solve.
        for (int f = N - 1; f >= 0; --f)
        {
            for (int q = 1; q <= S; ++q)
            {
                int sum = ARR[f];
                int sqr = ARR[f] * ARR[f];

                for (int len = 1; f + len - 1 < N; ++len)
                {
                    int avg = (int)((double)sum / len + 0.5);
                    int var = sqr - 2 * avg * sum + len * avg * avg;

                    MIN_UPDATE(CACHE[f][q], var + CACHE[f + len][q - 1]);

                    sum += ARR[f + len];
                    sqr += ARR[f + len] * ARR[f + len];
                }
            }
        }

        printf("%d\n", CACHE[0][S]);
    }

    return 0;
}