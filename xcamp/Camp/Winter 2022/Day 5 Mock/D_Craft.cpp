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

const int MAXN = 500010;
int N;
vector<int> nbs[MAXN];
int v[MAXN];
int sz[MAXN];
int dp[MAXN];

bool Comp(int a, int b)
{
    return dp[a] > dp[b];
}

void DP(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
        DP(nbs[a][i], a);
    
    sort(nbs[a].begin(), nbs[a].end(), Comp);

    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        dp[a] += sz[a] * 2;
        dp[nbs[a][i]] = max(0, dp[nbs[a][i]] - 1);
        sz[a] += sz[nbs[a][i]] + 1;
        dp[a] = max(dp[a], dp[nbs[a][i]] + sz[a] * 2) - sz[a] * 2;
    }

    if (a != 1) dp[a] = max(dp[a] + sz[a] * 2, v[a]) - sz[a] * 2;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> v[i];
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DP(1, 0);

    cout << max(dp[1], v[1]) + sz[1] * 2 << endl;
    return 0;
}