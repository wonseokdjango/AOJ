#include <algorithm>
#include <iostream>
#include <string>

#define MAXLEN 10001

using namespace std;

int C;
string PI;

int CACHE[MAXLEN];

int difficulty(int _idx, int _group)
{
    int idx;

    for (idx = 1; idx < _group; ++idx)
    {
        if (PI[_idx + idx] != PI[_idx])
            break;
    }

    if (idx == _group)
        return 1;

    for (idx = 1; idx < _group - 1; ++idx)
    {
        if (PI[_idx + idx + 1] - PI[_idx + idx] != PI[_idx + 1] - PI[_idx])
            break;
    }

    if (idx == _group - 1)
    {
        if (PI[_idx + 1] - PI[_idx] == 1 || PI[_idx + 1] - PI[_idx] == -1)
            return 2;
        else
            return 5;
    }

    int sign = -1;
    for (idx = 1; idx < _group - 1; ++idx)
    {
        if (PI[_idx + idx + 1] - PI[_idx + idx] != sign * (PI[_idx + 1] - PI[_idx]))
            break;
        sign *= -1;
    }

    if (idx == _group - 1)
        return 4;

    return 10;
}


int main(void)
{
    cin >> C;

    while (C--)
    {
        cin >> PI;

        // init.
        for (int i = 0; i < MAXLEN; ++i)
            CACHE[i] = 10 * MAXLEN;
        
        // base case.
        CACHE[PI.length()] = 0;
        CACHE[PI.length() - 1] = 10 * MAXLEN;
        CACHE[PI.length() - 2] = 10 * MAXLEN;
        
        // recursive step.
        for (int idx = PI.length() - 3; idx >= 0; --idx)
        {
            for (int group = 3; idx + group - 1 < PI.length() && group <= 5; ++group)
                CACHE[idx] = min(CACHE[idx], CACHE[idx + group] + difficulty(idx, group));
        }

        cout << CACHE[0] << endl;
    }
    
    return 0;
}