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

const int MAXN = 100010;
int N;
vector<int> nbs[MAXN];
int c[MAXN];
ll dp[MAXN][2];

void DP(int a)
{
    dp[a][0] = 1;
    dp[a][1] = 0;

    for (int i = 0; i < nbs[a].size(); i++)
    {
        DP(nbs[a][i]);

        dp[a][1] = mult(dp[a][1], dp[nbs[a][i]][0]);
        dp[a][1] = add(dp[a][1], mult(dp[a][0], dp[nbs[a][i]][1]));
        dp[a][0] = mult(dp[a][0], dp[nbs[a][i]][0]);
    }

    if (c[a]) dp[a][1] = dp[a][0];
    else dp[a][0] = add(dp[a][0], dp[a][1]);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++)
    {
        int a;
        cin >> a;
        nbs[a].pb(i);
    }

    for (int i = 0; i < N; i++) cin >> c[i];

    DP(0);
    cout << dp[0][1] << endl;
    return 0;
} 