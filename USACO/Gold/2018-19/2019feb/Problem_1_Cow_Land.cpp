/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
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
#define endl "\n"
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = LINF;
// ll MOD = 1000000007;
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
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

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
struct ST
{
    vector<ll> seg;

    ST() {ST(0);}

    ST(int n) {seg.resize(1 + 4 * n);}

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] ^ seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans ^= query(a, b, cid * 2, ss, mid);
        if (b > mid) ans ^= query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    }
};

int w[MAXN];
int sz[MAXN];
vector<int> nbs[MAXN];
int hchild[MAXN];
pii loc[MAXN];
ST chains[MAXN];
vector<int> nodes[MAXN];
int chainsz[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int T = 0;
void tour(int a, int p)
{
    lift[a][0] = p;
    for (int j = 1; j < 32; j++) 
        lift[a][j] = lift[lift[a][j - 1]][j - 1];
    in[a] = ++T;
    euler[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
    out[a] = ++T;
    euler[T] = -a;
}
bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
void setup_lca() {tour(1, 0);}
int lca(int a, int b)
{
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = 31; i >= 0; i--)
        if (lift[a][i] != 0 && !is_anc(lift[a][i], b)) a = lift[a][i];
    
    return lift[a][0];
}

bool Comp(int a, int b)
{
    return sz[a] < sz[b];
}

int C = 0;
void DFS(int a, int p)
{
    sz[a] = 1;
    vector<int> check;
    for (int nb : nbs[a]) if (nb != p)
    {
        DFS(nb, a);
        sz[a] += sz[nb];
        lift[nb][0] = a;
        check.pb(nb);
    }
    
    sort(check.rbegin(), check.rend(), Comp);
    if (check.size())
    {
        hchild[a] = check[0];
        loc[a] = pii(loc[hchild[a]].FF, loc[hchild[a]].SS + 1);
    }
    else 
    {
        loc[a] = pii(++C, 1);
        nodes[C].pb(0);
    }
    nodes[loc[a].FF].pb(a);
    chainsz[loc[a].FF]++;
}

void setup_hld()
{
    DFS(1, 0);
    setup_lca();
    for (int i = 1; i <= C; i++) 
    {
        chains[i] = ST(chainsz[i]);
        for (int j = 1; j <= chainsz[i]; j++)
            chains[i].update(j, w[nodes[i][j]], 1, 1, chainsz[i]);
    }
}

ll answer(int a, int b)
{
    int c = lca(a, b);

    int aloc = loc[a].FF;
    int bloc = loc[b].FF;
    ll ans = 0;
    while (a && loc[a].FF != loc[c].FF)
    {
        ans ^= chains[aloc].query(loc[a].SS, chainsz[aloc], 1, 1, chainsz[aloc]);
        a = lift[nodes[aloc][chainsz[aloc]]][0];
        aloc = loc[a].FF;
    }
    if (a) ans ^= chains[aloc].query(loc[a].SS, loc[c].SS, 1, 1, chainsz[aloc]);

    while (b && loc[b].FF != loc[c].FF)
    {
        ans ^= chains[bloc].query(loc[b].SS, chainsz[bloc], 1, 1, chainsz[bloc]);
        b = lift[nodes[bloc][chainsz[bloc]]][0];
        bloc = loc[b].FF;
    }
    if (b) ans ^= chains[bloc].query(loc[b].SS, loc[c].SS, 1, 1, chainsz[bloc]);

    ans ^= w[c];
    return ans;
}

int main()
{
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> w[i];

    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    setup_hld();

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int n, v;
            cin >> n >> v;
            w[n] = v;
            chains[loc[n].FF].update(loc[n].SS, v, 1, 1, chainsz[loc[n].FF]);
        }
        if (t == 2)
        {
            int a, b;
            cin >> a >> b;
            cout << answer(a, b) << endl;
        }
    }

    return 0;
} 