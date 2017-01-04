#include <cstdio>

#define MAXH 20
#define MAXW 20
#define NUMOFBLOCKS 4
#define NUMOFBLANKS 3

const int dr[NUMOFBLOCKS][NUMOFBLANKS] = {
    {0,  0,  1},
    {0,  0,  1},
    {0,  1,  1},
    {0,  1,  1}
};
const int dc[NUMOFBLOCKS][NUMOFBLANKS] = {
    {0,  1,  0},
    {0,  1,  1},
    {0, -1,  0},
    {0,  0,  1}
};

int C, H, W;
char BOARD[MAXH][MAXW];

int solve(void);
bool safe(int, int);

int main(void)
{
    scanf(" %d", &C);
    while (C--)
    {
        scanf(" %d %d", &H, &W);
        for (int r = 0; r < H; ++r)
            scanf(" %[^\n]%*c", BOARD[r]);

        printf("%d\n", solve());
    }

    return 0;
}

int solve(void)
{
    int r, c;
    for (r = 0; r < H; ++r)
    {
        for (c = 0; c < W; ++c)
        {
            if (BOARD[r][c] == '.')
                break;
        }

        if (c != W)
            break;
    }

    if (r == H && c == W)
        return 1;

    int ret = 0;
    for (int blk = 0; blk < NUMOFBLOCKS; ++blk)
    {
        int idx;
        for (idx = 0; idx < NUMOFBLANKS; ++idx)
        {
            if (
                !safe(r + dr[blk][idx], c + dc[blk][idx]) ||
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] != '.')
                break;
        }
        // you can put blk-th block.
        if (idx == NUMOFBLANKS)
        {
            for (idx = 0; idx < NUMOFBLANKS; ++idx)
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] = '#';
            ret += solve();
            for (idx = 0; idx < NUMOFBLANKS; ++idx)
                BOARD[r + dr[blk][idx]][c + dc[blk][idx]] = '.';
        }
    }

    return ret;
}

bool safe(int _r, int _c)
{
    return (0 <= _r && _r < H && 0 <= _c && _c < W);
}
