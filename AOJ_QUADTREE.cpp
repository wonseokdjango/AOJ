#include <cstdio>
#include <string>
#include <iostream>

//#define WONSEOK_REDIRECT

using namespace std;

int C;
string QUADTREE;

string solve(int);

int main(void)
{

#ifdef WONSEOK_REDIRECT
    freopen("in.txt", "r", stdin);
#endif // WONSEOK_REDIRECT

    cin >> C;

    while (C--)
    {
        cin >> QUADTREE;
        cout << solve(0) << endl;
    }

    return 0;
}

string solve(int pos)
{
    // base case.
    if (QUADTREE[pos] != 'x')
    {
        return QUADTREE.substr(pos,  1);
    }

    // recursive step.
    string ul, ur, ll, lr;
    ul = solve(pos + 1);
    ur = solve(pos + 1 + ul.size());
    ll = solve(pos + 1 + ul.size() + ur.size());
    lr = solve(pos + 1 + ul.size() + ur.size() + ll.size());

    return "x" + ll + lr + ul + ur;
}
