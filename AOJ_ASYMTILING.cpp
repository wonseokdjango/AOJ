#include <cstdio>

typedef unsigned long long u64t;

#define MOD 1000000007

int C;
int N;

u64t fibo(int _n)
{
    if (0 == _n)
        return 1;
    if (1 == _n)
        return 1;

    u64t tmp;
    u64t pre = 1;
    u64t cur = 1;
    while (_n-- > 1)
    {
        tmp = pre;
        pre = cur;
        cur = (tmp + cur) % MOD;
    }

    return cur;
}

int main(void)
{
    scanf(" %d", &C);
    while (C--)
    {
        scanf(" %d", &N);
        
        u64t ans = 0;

        if (1 == N)
            ans = 0;
        else if (2 == N)
            ans = 0;
        else if (3 == N)
            ans = 2;
        else if (4 == N)
            ans = 2;
        else if (0 == N % 2)
        {
            ans += fibo(N);
            ans += 2 * MOD;
            ans -= 2 * fibo((N - 2) / 2);
            ans %= MOD;
            ans += MOD;
            ans -= fibo((N - 4) / 2);
            ans %= MOD;
        }
        else
        {
            ans += fibo(N);
            ans += MOD;
            ans -= fibo((N - 1) / 2);
            ans %= MOD;
        }

        printf("%lld\n", ans);
    }

    return 0;
}