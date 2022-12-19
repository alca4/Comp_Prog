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
int N, Q;

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

vector<pii> paths;
vector<pii> queries;
vector<int> nbs[MAXN];
int vis[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int T = 0;
void tour(int a, int p)
{
    vis[a] = 1;
    in[a] = ++T;
    euler[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
    out[a] = ++T;
    euler[T] = a;
}
int lift[MAXN][32];
bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
void setup_blift()
{
    for (int i = 1; i <= N; i++)
        for (int j = 1; j < 32; j++) lift[i][j] = lift[lift[i][j - 1]][j - 1];
}
int lca(int a, int b)
{
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    int c = a;
    while (!is_anc(c, b))
    {
        for (int i = 31; i >= 0; i--)
            if (!is_anc(c, b)) c = lift[c][i];
        c = lift[c][0];
    }

    return c;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    setup_dsu();
    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            p[x] = y;
            nbs[y].pb(x);
        }
        if (t == 2) 
        {
            int x;
            cin >> x;
            paths.pb(pii(x, root(x)));
        }
        if (t == 3)
        {
            int x, y;
            cin >> x >> y;
            queries.pb(pii(x, y));
        }
    }

    for (int i = 1; i <= N; i++) if (!vis[root(i)]) tour(root(i), -1);

    for (int i = 0; i < queries.size(); i++)
    {
        int n = queries[i].FF;
        int p = queries[i].SS;

        int s = paths[p - 1].FF;
        int e = paths[p - 1].SS;

        if (is_anc(n, s) && is_anc(e, n)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    return 0;
}