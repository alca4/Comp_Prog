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
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

typedef pair<short, short> pii;
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

const int MAXN = 301;
int N, M, P;
int grid[MAXN][MAXN];
vector<short> hi[MAXN];
vector<pii> locs[MAXN * MAXN];
int dp[MAXN][MAXN];
bool vis[MAXN][MAXN];

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P;
    queue<pii> search;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++)
    {
        cin >> grid[i][j];
        locs[grid[i][j]].pb(pii(i, j));
        if (grid[i][j] == 1)
        {
            search.push(pii(i, j));
            vis[i][j] = 1;
            dp[i][j] = i - 1 + j - 1;
        }
        else dp[i][j] = INF;
    }

    int cnt = 0;
    // cout << search.size() << endl;
    while (!search.empty())
    {
        int x = search.front().FF;
        int y = search.front().SS;
        search.pop();

        vector<pii> nbs;

        if (grid[x][y] > cnt)
        {
            for (int j = 1; j <= N; j++) hi[j].clear();
            locs[cnt].clear();
            cnt++;
            for (int j = 0; j < locs[cnt + 1].size(); j++) 
            hi[locs[cnt + 1][j].FF].pb(locs[cnt + 1][j].SS);
        }
        if (grid[x][y] == P) cout << dp[x][y] << endl;

        for (int k = 1; k <= N; k++)
        {
            // cout << locs[i][j].FF << " " << locs[i][j].SS << endl;
            auto it = upper_bound(hi[k].begin(), hi[k].end(), y);
            if (it != hi[k].end()) nbs.pb(pii(k, *it));
            if (it != hi[k].begin()) nbs.pb(pii(k, *(--it)));
        }

        for (pii nb : nbs)
        {
            mineq(dp[nb.FF][nb.SS], dp[x][y] + abs(x - nb.FF) + abs(y - nb.SS));
            if (!vis[nb.FF][nb.SS]) 
            {
                search.push(pii(nb.FF, nb.SS));
                vis[nb.FF][nb.SS] = 1;
            }
        }
    }

    return 0;
} 