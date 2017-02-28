#include <cstdio>

#define MAXN 100
#define MOD 10000000

int C;
int N;
int CACHE[MAXN + 1][MAXN + 1];

int main(void)
{
    // pre-processing.
    for (int total = 1; total <= MAXN; ++total)
    {
        for (int top = 1; top < total; ++top)
        {
            CACHE[total][top] = 0;
            for (int under = 1; under <= total - top; ++under)
            {
                CACHE[total][top] += (top + under - 1) * CACHE[total - top][under];
                CACHE[total][top] %= MOD;
            }
        }
        CACHE[total][total] = 1;
    }

    // solve.
    scanf(" %d", &C);
    while (C--)
    {
        scanf(" %d", &N);

        int ans = 0;
        for (int top = 1; top <= N; ++top)
            ans = (ans + CACHE[N][top]) % MOD;

        printf("%d\n", ans);
    }

    return 0;
}