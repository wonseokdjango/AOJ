#include <cstdio>
#include <algorithm>

#define MAXN 1001
#define MAXAVG 100001

int N, C, L;
int COST[1001];

double solve(void);

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        scanf(" %d %d", &N, &L);
        for (int l = 0; l < N; ++l)
        {
            scanf(" %d", &COST[l]);
        }

        printf("%.15lf\n", solve());
    }

    return 0;
}

double solve(void)
{
    int sum = 0;
    double avg = MAXAVG;

    for (int s = 0; s <= N - L; ++s)
    {
        // initial min avg from s to s + L - 1.
        sum = 0;
        for (int l = 0; l < L; ++l)
        {
            sum += COST[s + l];
        }
        avg = std::min(avg, (double)sum / L);

        // min avg from s to e.
        for (int e = s + L; e < N; ++e)
        {
            sum += COST[e];
            avg = std::min(avg, (double)sum / (e - s + 1));
        }
    }

    return avg;
}
