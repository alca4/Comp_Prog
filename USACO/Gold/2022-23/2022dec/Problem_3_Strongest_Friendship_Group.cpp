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
int N, M;
vector<int> nbs[MAXN];

int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

int deg[MAXN];
set<pii> vals;
int label[MAXN];
vector<int> family[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
        deg[a]++, deg[b]++;
    }

    for (int i = 1; i <= N; i++) vals.insert({deg[i], i});

    for (int i = 1; i <= N; i++)
    {
        while (vals.size() && vals.begin()->FF <= i)
        {
            int n = vals.begin()->SS;
            vals.erase(vals.begin());
            label[n] = i;
            for (int i = 0; i < nbs[n].size(); i++)
            {
                int nb = nbs[n][i];
                if (label[nb]) continue;
                vals.erase(vals.find({deg[nb], nb}));
                vals.insert({deg[nb] - 1, nb});
                deg[nb]--;
            }
        }
    }

    setup_dsu();
    for (int i = 1; i <= N; i++) family[label[i]].pb(i);

    ll ans = 0;
    for (int i = N; i >= 1; i--)
    {
        for (int j = 0; j < family[i].size(); j++)
        {
            int n = family[i][j];
            for (int k = 0; k < nbs[n].size(); k++)
            {
                if (label[nbs[n][k]] >= label[n]) combine(n, nbs[n][k]);
            }
        }
        for (int j = 0; j < family[i].size(); j++)
        {
            int n = family[i][j];
            ans = max(ans, 1ll * sz[root(n)] * i);
        }
    }

    cout << ans << endl;

    // for (int i = 1; i <= N; i++) cout << label[i] << " ";
    // cout << endl;
    return 0;
} 