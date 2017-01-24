#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

#define TRUE   1
#define FALSE  2
#define MAXLEN 100

using namespace std;

int C, N;
string WILD;
string NAME;
vector<string> ANSWER;
char CACHE[MAXLEN][MAXLEN];

char solve(int wIdx, int nIdx);

int main(void)
{
    cin >> C;

    while (C--)
    {
        ANSWER.clear();

        cin >> WILD;
        cin >> N;
        
        for (int w = 0; w < N; ++w)
        {
            cin >> NAME;
            
            memset(CACHE, 0, sizeof(char) * MAXLEN * MAXLEN);
            if (solve(0, 0) == TRUE)
                ANSWER.push_back(NAME);
        }

        sort(ANSWER.begin(), ANSWER.end());

        for (int ans = 0; ans < ANSWER.size(); ++ans)
            cout << ANSWER[ans] << endl;
    }

    return 0;
}

char solve(int wIdx, int nIdx)
{
    // base cases.
    if (wIdx == WILD.size())
        return (nIdx == NAME.size()) ? TRUE : FALSE;
    if (nIdx == NAME.size())
    {
        int idx;
        for (idx = wIdx; idx < WILD.size() && WILD[idx] == '*'; ++idx);

        return (idx == WILD.size()) ? TRUE : FALSE;
    }

    // dp step.
    char& ret = CACHE[wIdx][nIdx];
    if (ret == 0)
    {
        // dp.
        if (WILD[wIdx] == '?')
            ret = solve(wIdx + 1, nIdx + 1);
        else if (WILD[wIdx] == '*')
        {
            ret = FALSE;
            for (int rep = 0; rep <= NAME.size() - nIdx; ++rep)
            {
                if (solve(wIdx + 1, nIdx + rep) == TRUE)
                {
                    ret = TRUE;
                    break;
                }
            }
        }
        else
            ret = (WILD[wIdx] == NAME[nIdx] && solve(wIdx + 1, nIdx + 1) == TRUE) ? TRUE : FALSE;
    }

    return ret;
}
