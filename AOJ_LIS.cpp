#include <cstdio>
#include <cstring>

#define MAXN 500
#define MAXVAL(A, B) ( ( (A) > (B) ) ? (A) : (B) )

int C, N;
int CACHE[MAXN];
int NUMBERS[MAXN];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        // input.
        scanf(" %d", &N);
        for (int idx = 0; idx < N; ++idx)
            scanf(" %d", &NUMBERS[idx]);

        // solve.
        for (int cur = 0; cur < N; ++cur)
        {
            CACHE[cur] = 1;
            for (int pre = cur - 1; pre >= 0; --pre)
            {
                if (NUMBERS[pre] < NUMBERS[cur])
                    CACHE[cur] = MAXVAL(CACHE[cur], CACHE[pre] + 1);
            }
        }

        int ans = 0;
        for (int idx = 0; idx < N; ++idx)
            ans = MAXVAL(ans, CACHE[idx]);

        // answer.
        printf("%d\n", ans);
    }

    return 0;
}