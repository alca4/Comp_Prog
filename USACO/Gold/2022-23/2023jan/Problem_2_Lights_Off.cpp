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
int INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

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

const int MAXN = 21;
int N;
int dp[MAXN][1 << MAXN];

void solve()
{
    // cout << "==========" << endl;
    int a = 0, b = 0;
    for (int i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        a |= (c - '0') << (N - i - 1);
    }
    for (int i = 0; i < N; i++)
    {
        char c;
        cin >> c;
        b |= (c - '0') << (N - i - 1);
    }

    if (!a) 
    {
        cout << 0 << "\n";
        return;
    }

    for (int i = 1; i <= N; i++)
    {
        a ^= b;

        if (b & 1) b += (1 << N);
        b = (b >> 1);

        if (dp[i][a])
        {
            cout << i << "\n";
            return;
        }
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T >> N;

    dp[0][0] = 1;
    for (int i = 1; i <= N; i++) for (int mask = 0; mask < (1 << N); mask++)
    {
        int change = (1 << i) - 1;
        int t1 = change, t2 = 0;
        for (int j = 0; j < N; j++)
        {
            if (t1 >= (1 << N))
            {
                t2 = (t2 << 1) + 1;
                t1 -= (1 << N);
            }
            if (dp[i - 1][t1 ^ mask ^ t2]) dp[i][mask] = 1;
            t1 = (t1 << 1);
        }
    }

    while (T--) solve();
    return 0;
} 