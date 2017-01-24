#include <cstdio>
#include <cstring>

#define MAXH 100
#define MAXVAL(A, B) ( ( (A) > (B) ) ? (A) : (B) )

int C, H;
int TRIANGLE[MAXH][MAXH];

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        // input.
        scanf(" %d", &H);
        for (int h = 0; h < H; ++h)
        {
            for (int idx = 0; idx < h + 1; ++idx)
                scanf(" %d", &TRIANGLE[h][idx]);
        }

        // solve.
        for (int h = H - 2; h >= 0; --h)
        {
            for (int idx = 0; idx < h + 1; ++idx)
                TRIANGLE[h][idx] += MAXVAL(TRIANGLE[h + 1][idx], TRIANGLE[h + 1][idx + 1]);
        }

        // answer.
        printf("%d\n", TRIANGLE[0][0]);
    }

    return 0;
}