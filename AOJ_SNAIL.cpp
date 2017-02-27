#include <cstdio>
#include <cstring>

#define MAX_H 1000
#define MAX_DAY 1000

int C;
int H, DAY;
double CACHE[MAX_DAY + 1][MAX_H + 1];

int main(void)
{
    scanf(" %d", &C);
    while (C--)
    {
        // init.
        memset(CACHE, 0, sizeof(double) * (MAX_DAY + 1) * (MAX_H + 1));
        for (int day = 0; day < MAX_DAY + 1; ++day)
            CACHE[day][0] = 1.0;
        for (int day = 1; day < MAX_DAY + 1; ++day)
            CACHE[day][1] = 1.0;
        
        // input.
        scanf(" %d %d", &H, &DAY);
       
        // solve.
        for (int day = 1; day <= DAY; ++day)
        {
            for (int h = 2; h <= H; ++h)
            {
                CACHE[day][h] = 0.25 * CACHE[day - 1][h - 1] + 0.75 * CACHE[day - 1][h - 2];
            }
        }
        printf("%.10lf\n", CACHE[DAY][H]);
    }

    return 0;
}