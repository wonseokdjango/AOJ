#include <cstdio>
#include <cstring>

#define MAXN 10

int C, N, M;
bool IS_PAIRED[MAXN];
bool IS_FRIEND[MAXN][MAXN];

int solve(void);

int main(void)
{
	scanf(" %d", &C);

	while (C--)
	{
		memset(IS_PAIRED, 0, sizeof(bool) * MAXN);
		memset(IS_FRIEND, 0, sizeof(bool) * MAXN * MAXN);

		scanf(" %d %d", &N, &M);
		for (int l = 0; l < M; ++l)
		{
			int u, v;
			scanf(" %d %d", &u, &v);
			IS_FRIEND[u][v] = IS_FRIEND[v][u] = true;
		}

		printf("%d\n", solve());
	}

	return 0;
}

int solve(void)
{
	int idx;
	for (idx = 0; idx < N && IS_PAIRED[idx]; ++idx);

	if (idx == N)
		return 1;

	int ret = 0;
	for (int l = 0; l < N; ++l)
	{
		if (!IS_PAIRED[l] && IS_FRIEND[idx][l])
		{
			IS_PAIRED[idx] = IS_PAIRED[l] = true;
			ret += solve();
			IS_PAIRED[idx] = IS_PAIRED[l] = false;
		}
	}

	return ret;
}