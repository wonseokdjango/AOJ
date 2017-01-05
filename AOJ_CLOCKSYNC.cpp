#include <cstdio>

#define MAXCNT 64
#define MAXTRIGGER 6
#define NUMOFCLOCKS 16
#define NUMOFBUTTONS 10

const int TRIGGER[NUMOFCLOCKS][MAXTRIGGER] = {
    {0, 1, 2, -1},
    {3, 7, 9, 11, -1},
    {4, 10, 14, 15, -1},
    {0, 4, 5, 6, 7, -1},
    {6, 7, 8, 10, 12, -1},
    {0, 2, 14, 15, -1},
    {3, 14, 15, -1},
    {4, 5, 7, 14, 15, -1},
    {1, 2, 3, 4, 5, -1},
    {3, 4, 5, 9, 13, -1}
};

int C, CNT;
int CLOCKS[NUMOFCLOCKS];

void solve(int, int);

int main(void)
{
    scanf(" %d", &C);

    while (C--)
    {
        for (int clk = 0; clk < NUMOFCLOCKS; ++clk)
        {
            scanf(" %d", &CLOCKS[clk]);
            CLOCKS[clk] %= 12;
        }

        CNT = MAXCNT;
        solve(0, 0);
        printf("%d\n", (CNT == MAXCNT) ? -1 : CNT);
    }

    return 0;
}

void solve(int btn, int cnt)
{
    int clk;
    for (clk = 0; clk < NUMOFCLOCKS && CLOCKS[clk] == 0; ++clk);
    if (clk == NUMOFCLOCKS)
    {
        CNT = (CNT > cnt) ? cnt : CNT;
        return;
    }

    if (btn == NUMOFBUTTONS)
        return;

    // click btn-th button.
    int idx;
    for (int click = 0; click < 4 && cnt + click < CNT; ++click)
    {
        idx = 0;
        while (TRIGGER[btn][idx] != -1)
        {
            CLOCKS[TRIGGER[btn][idx]] = (CLOCKS[TRIGGER[btn][idx]] + 3 * click) % 12;
            ++idx;
        }

        solve(btn + 1, cnt + click);

        idx = 0;
        while (TRIGGER[btn][idx] != -1)
        {
            CLOCKS[TRIGGER[btn][idx]] = (CLOCKS[TRIGGER[btn][idx]] + 9 * click) % 12;
            ++idx;
        }
    }
}
