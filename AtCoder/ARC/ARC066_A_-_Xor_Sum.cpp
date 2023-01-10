/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

ll N;
ll dp[65][3];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    N *= 2;
    dp[(int) log2(N)][0] = 1;
    for (int i = (int) log2(N); i > 0; i--)
    {
        if (N & (1ll << i))
        {
            dp[i - 1][0] = add(dp[i][0], dp[i - 1][0]);
            dp[i - 1][1] = add(dp[i][0], dp[i - 1][1]);
        }
        else
        {
            dp[i - 1][0] = add(dp[i][0], dp[i - 1][0]);
        }

        if (N & (1ll << i))
        {
            dp[i - 1][2] = add(mult(dp[i][1], 2), dp[i - 1][2]);
            dp[i - 1][1] = add(dp[i][1], dp[i - 1][1]);
        }
        else
        {
            dp[i - 1][0] = add(dp[i][1], dp[i - 1][0]);
            dp[i - 1][1] = add(dp[i][1], dp[i - 1][1]);
            dp[i - 1][2] = add(dp[i][1], dp[i - 1][2]);
        }

        dp[i - 1][2] = add(dp[i - 1][2], mult(dp[i][2], 3));
    }

    cout << add(dp[0][0], add(dp[0][1], dp[0][2])) << endl;
    return 0;
}