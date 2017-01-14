#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define THRESHOLD 64

using namespace std;

int C, BASE;
vector<int> MEMBER, FAN;

void add(vector<int>& dest, const vector<int>& src, int pow);
void sub(vector<int>& dest, const vector<int>& src, int pow);

void normalize(vector<int>& num);
vector<int> bf(const vector<int>&, const vector<int>&);
vector<int> dq(const vector<int>&, const vector<int>&);

bool notZero(int num);

int main(void)
{
    cin >> C;

    while (C--)
    {
        MEMBER.clear();
        FAN.clear();

        string member, fan;
        cin >> member >> fan;

        for (int idx = 0; idx < member.size(); ++idx)
            MEMBER.push_back((member[idx] == 'M') ? 1 : 0);
        for (int idx = fan.size() - 1; idx >= 0; --idx)
            FAN.push_back((fan[idx] == 'M') ? 1 : 0);

        BASE = member.size() + 1; 
        int total = fan.size() - member.size() + 1;
        
        normalize(MEMBER);
        normalize(FAN);
        vector<int> product = dq(MEMBER, FAN);

        int s = member.size() - 1;
        int e = fan.size() - 1;
        int handshake = 0;
        for (int idx = s; idx <= e && 0 <= idx && idx < product.size(); ++idx)
        {
            if (product[idx])
                ++handshake;
        }
        cout << total - handshake << endl;
    }

    return 0;
}

void add(vector<int>& dest, const vector<int>& src, int pow)
{
    dest.resize(max<int>(dest.size(), src.size()) + pow, 0);
    
    for (int idx = 0; idx < src.size(); ++idx)
    {
        dest[idx + pow] += src[idx];
    }
    
    normalize(dest);
}

void sub(vector<int>& dest, const vector<int>& src, int pow)
{
    dest.resize(max<int>(dest.size(), src.size()) + pow, 0);

    for (int idx = 0; idx < src.size(); ++idx)
    {
        dest[idx + pow] -= src[idx];
    }

    normalize(dest);
}

void normalize(vector<int>& num)
{
    int cio;

    num.push_back(0);

    for (int idx = 0; idx < num.size() - 1; ++idx)
    {
        if (num[idx] < 0)
        {
            cio = (BASE - 1 - num[idx]) / BASE;
            num[idx + 1] -= cio;
            num[idx] += cio * BASE;
        }
        else if (num[idx] >= BASE)
        {
            cio = num[idx] / BASE;
            num[idx + 1] += cio;
            num[idx] %= BASE;
        }
    }

    while (!num.empty() && *num.rbegin() == 0)
        num.pop_back();
}

vector<int> bf(const vector<int>& a, const vector<int>& b)
{
    vector<int> ret(a.size() + b.size() - 1, 0);

    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
        {
            ret[i + j] += a[i] * b[j];
        }
    }

    normalize(ret);

    return ret;
}

vector<int> dq(const vector<int>& a, const vector<int>& b)
{
    int asize = a.size();
    int bsize = b.size();

    // base case.
    if (asize == 0 || bsize == 0)
        return vector<int>();
    if (asize < bsize)
        return dq(b, a);
    if (asize <= THRESHOLD)
        return bf(a, b);

    // recursive step.
    int m = asize / 2;
    vector<int> a0(a.begin(), a.begin() + m);
    vector<int> a1(a.begin() + m, a.end());
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), m));
    vector<int> b1(b.begin() + min<int>(b.size(), m), b.end());

    vector<int> z0 = dq(a0, b0);
    vector<int> z2 = dq(a1, b1);

    add(a0, a1, 0);
    add(b0, b1, 0);
    vector<int> z1 = dq(a0, b0);
    sub(z1, z0, 0);
    sub(z1, z2, 0);

    vector<int> ret;
    add(ret, z0, 0);
    add(ret, z1, m);
    add(ret, z2, m + m);

    return ret;
}

bool notZero(int num)
{
    return (num != 0);
}
