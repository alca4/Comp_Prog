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
ll INF = INT_MAX;
ll LINF = LONG_MAX;
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

const int MAXN = 100010;
int N, S, D;
int x[MAXN], y[MAXN];
unordered_map<int, map<int, int>> xloc;
unordered_map<int, map<int, int>> yloc;
unordered_map<int, vector<pii>> xloc2;
unordered_map<int, vector<pii>> yloc2;
ll fact[MAXN], factinv[MAXN];
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

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

int siz = 0;

void DFS(int a, int p)
{
    vector<int> nbs;
    auto s = xloc[x[a] + D].lower_bound(y[a] - D);
    for (; s != xloc[x[a] + D].end() && s->FF <= y[a] + D; s++) nbs.pb(s->SS);

    s = xloc[x[a] - D].lower_bound(y[a] - D);
    for (; s != xloc[x[a] - D].end() && s->FF <= y[a] + D; s++) nbs.pb(s->SS);

    s = yloc[y[a] + D].upper_bound(x[a] - D);
    for (; s != yloc[y[a] + D].end() && s->FF < x[a] + D; s++) nbs.pb(s->SS);

    s = yloc[y[a] - D].upper_bound(x[a] - D);
    for (; s != yloc[y[a] - D].end() && s->FF < x[a] + D; s++) nbs.pb(s->SS);

    for (int nb : nbs) 
    {
        xloc[x[nb]].erase(y[nb]);
        yloc[y[nb]].erase(x[nb]);
        combine(a, nb);
    }

    siz += nbs.size();

    for (int nb : nbs) DFS(nb, a);
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a;
    cin >> N >> S >> a;
    for (int i = 1; i <= N; i++) 
    {
        int tx, ty;
        cin >> tx >> ty;
        x[i] = tx + ty;
        y[i] = ty - tx;
        // cout << x[i] << " " << y[i] << endl;

        xloc[x[i]][y[i]] = i;
        yloc[y[i]][x[i]] = i;
    }
    D = max(abs(x[S] - x[a]), abs(y[S] - y[a]));

    setup_dsu();

    xloc[x[S]].erase(y[S]);
    yloc[y[S]].erase(x[S]);

    DFS(S, 0);

    // cout << siz << endl;

    xloc.clear();
    yloc.clear();

    for (int i = 1; i <= N; i++) if (root(i) == root(S)) 
    {
        // cout << x[i] << " " << y[i] << " " << i << endl;
        xloc2[x[i]].pb({y[i], i});
        yloc2[y[i]].pb({x[i], i});
    }
    for (auto n : xloc2) sort(xloc2[n.FF].begin(), xloc2[n.FF].end());
    for (auto n : yloc2) sort(yloc2[n.FF].begin(), yloc2[n.FF].end());

    ll ans = 0;
    for (int i = 1; i <= N; i++) if (root(i) == root(S)) 
    {
        // cout << "i is: " << i << endl;
        ans += distance(upper_bound(xloc2[x[i] + D].begin(), xloc2[x[i] + D].end(), pii(y[i] - D, 0)),
                        upper_bound(xloc2[x[i] + D].begin(), xloc2[x[i] + D].end(), pii(y[i] + D, INF)));
        // cout << ans << endl;

        ans += distance(upper_bound(xloc2[x[i] - D].begin(), xloc2[x[i] - D].end(), pii(y[i] - D, 0)),
                        upper_bound(xloc2[x[i] - D].begin(), xloc2[x[i] - D].end(), pii(y[i] + D, INF)));
        // cout << ans << endl;
        
        ans += distance(upper_bound(yloc2[y[i] + D].begin(), yloc2[y[i] + D].end(), pii(x[i] - D, INF)),
                        upper_bound(yloc2[y[i] + D].begin(), yloc2[y[i] + D].end(), pii(x[i] + D, 0)));
        // cout << ans << endl;
        
        ans += distance(upper_bound(yloc2[y[i] - D].begin(), yloc2[y[i] - D].end(), pii(x[i] - D, INF)),
                        upper_bound(yloc2[y[i] - D].begin(), yloc2[y[i] - D].end(), pii(x[i] + D, 0)));
        // cout << ans << endl;
    }

    cout << ans / 2 << endl;
    return 0;
} 