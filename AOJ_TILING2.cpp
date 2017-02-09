#include <cstdio>

#define MOD 1000000007

int C;
int N;

int fibo(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    int p = 2;
    int pp = 1;
    int cur = p + pp;

    for (int i = 3; i < n; ++i)
    {
        pp = p;
        p = cur;
        cur = (p + pp) % MOD;
    }

    return cur;
}


int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        scanf(" %d", &N);
        printf("%d\n", fibo(N));
    }

    return 0;
}