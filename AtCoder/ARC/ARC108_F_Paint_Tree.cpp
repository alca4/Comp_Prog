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

const int MAXN = 200010;
int N;
vector<int> nbs[MAXN];
set<pii, greater<pii>> dp[MAXN];
int vis[MAXN][2];
int dist[MAXN][2];
ll pow2[MAXN];
map<int, int> freq;

void DFS(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        DFS(nbs[a][i], a);
        if (dp[nbs[a][i]].empty()) dp[a].insert({1, nbs[a][i]});
        else dp[a].insert({dp[nbs[a][i]].begin()->FF + 1, dp[nbs[a][i]].begin()->SS});
    }
}

void DFN(int a, int t)
{
    queue<pii> search;
    search.push({a, 0});

    while (!search.empty())
    {
        int n = search.front().FF;
        int d = search.front().SS;
        search.pop();

        if (vis[n][t]) continue;
        dist[n][t] = d;
        vis[n][t] = 1;

        for (int i = 0; i < nbs[n].size(); i++)
            search.push({nbs[n][i], d + 1});
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    pow2[0] = 1;
    for (int i = 1; i <= N + 1; i++) pow2[i] = mult(pow2[i - 1], 2);
    pow2[0] = 0;
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);
    int a, b, d = 0;
    for (int i = 1; i <= N; i++) 
    {
        if (dp[i].size() >= 2)
        {
            auto f = dp[i].begin();
            auto s = ++f;
            --f;

            if (f->FF + s->FF > d)
            {
                d = f->FF + s->FF;
                a = f->SS, b = s->SS;
            }
        }
        if (dp[i].size() == 1)
        {
            auto f = dp[i].begin();
            if (f->FF > d)
            {
                d = f->FF;
                a = f->SS, b = i;
            }
        }
    }

    DFN(a, 0);
    DFN(b, 1);

    vector<int> sw1(d + 1), sw2(d + 1);

    for (int i = 1; i <= N; i++)
    {
        sw1[min(dist[i][0], dist[i][1])]++;
        sw2[max(dist[i][0], dist[i][1])]++;
    }

    ll ans = mult(d, pow2[N - 1]);
    int x = 0, y = 0;
    for (int i = 0; i < d; i++)
    {
        y += sw1[i];
        y -= sw2[i];
        x += sw2[i];
        ans = add(ans, pow2[N - 1]);
        if (x + y < N) continue;
        ll tmp = 0;
        ans = sub(ans, pow2[x + 1]);
    }

    cout << ans << endl;
    return 0;
} 