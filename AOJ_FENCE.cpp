#include <cstdio>
#include <algorithm>

//#define WONSEOK_REDIRECT
#define MAXFENCES 20000

using namespace std;

int C, N;
int FENCES[MAXFENCES] = { 0, };

int solve(int, int);

int main(void)
{
#ifdef WONSEOK_REDIRECT
    freopen("in.txt", "r", stdin);
#endif
    scanf(" %d", &C);

    while (C--)
    {
        scanf(" %d", &N);
        for (int fence = 0; fence < N; ++fence)
            scanf(" %d", &FENCES[fence]);

        printf("%d\n", solve(0, N - 1));
    }

    return 0;
}

int solve(int s, int e)
{
    // base cases.
    if (s > e)
        return 0;
    if (s == e)
        return FENCES[s];

    // recursive step(divide in 3 cases).
    int m = (s + e) / 2;
    int lsub = solve(s, m - 1);
    int rsub = solve(m + 1, e);

    int l = m;
    int r = m;
    int h = FENCES[m];
    int msub = FENCES[m];

    while (s <= l && r <= e)
    {
        int lh = (l - 1 < s) ? 0 : FENCES[l - 1];
        int rh = (r + 1 > e) ? 0 : FENCES[r + 1];

        if (lh < rh)
        {
            ++r;
            h = min(h, rh);
            msub = max(msub, h * (r - l + 1));
        }
        else
        {
            --l;
            h = min(h, lh);
            msub = max(msub, h * (r - l + 1));
        }
    }

    return max(msub, max(lsub, rsub));
}
