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
ll LINF = 9000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}

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

const int MAXN = 200010;
int N, T;
vector<int> nbs[MAXN];
int g[MAXN], h[MAXN];
ll fact[MAXN], factinv[MAXN];
ll dp[MAXN][2], sum[MAXN], sz[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[N]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

bool Comp(int a, int b)
{
    return sz[a] * sum[b] < sz[b] * sum[a];
}

void DFS(int a)
{
    sum[a] = g[a];
    sz[a] = 1;
    vector<ll> dps, sumvs, dpvs;
    for (int nb : nbs[a])
    {
        DFS(nb);
        dps.pb(nb);
        sum[a] += sum[nb];
        sz[a] += sz[nb];
        maxeq(h[a], h[nb] + 1);
    }

    sort(dps.begin(), dps.end(), Comp);

    ll t = 1;
    for (int i = 0; i < dps.size(); i++) 
    {
        sumvs.pb(sum[dps[i]]);
        dpvs.pb(sum[dps[i]] * t + dp[dps[i]][0]);
        t += sz[dps[i]] * 2;
        if (i) 
        {
            dpvs[i] += dpvs[i - 1];
            sumvs[i] += sumvs[i - 1];
        }
    }

    ll ans = LINF;
    for (int i = 0; i < dps.size(); i++) if (h[dps[i]] == h[a] - 1) 
    {
        ll tval = (dpvs[dpvs.size() - 1] - dpvs[i]) - 
                   2ll * sz[dps[i]] * (sumvs[sumvs.size() - 1] - sumvs[i]);
        if (i) tval += dpvs[i - 1];
        // cout << a << " mineqing " << ans << " with " << tval + sum[dps[i]] * t + dp[dps[i]][1] << endl;
        mineq(ans, tval + sum[dps[i]] * (2 * (sz[a] - 1 - sz[dps[i]]) + 1) + dp[dps[i]][1]);
    }

    if (dps.size())
    {
        dp[a][0] = dpvs[dpvs.size() - 1];
        dp[a][1] = ans;
    }
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> T;
    for (int i = 2; i <= N; i++) 
    {
        int n;
        cin >> n >> g[i];
        nbs[n].pb(i);
    }

    DFS(1);

    int maxh = 0;
    if (T) maxh = h[1];

    cout << (N - 1) * 2 - maxh << " " << dp[1][T] << endl;

    return 0;
} 