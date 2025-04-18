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

Tooting Bec
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
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 100010;

struct DSU {
    vector<int> p, sz;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    }

    int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
    int combine(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};

int N;
int a[MAXN];
vector<int> nbs[MAXN];
int vis[MAXN];

vector<int> dfs;
int DFS(int a, int p, int c) {
    if (vis[a]) {
        int ret = 0;
        while (dfs.back() != a) {
            dfs.pop_back();
            ret++;
        }
        dfs.pop_back();
        return ret + 1;
    }
    vis[a] = 1;

    dfs.pb(a);

    int seen_parent = 0;
    for (int nb : nbs[a]) {
        if (seen_parent || nb != p) {
            int ret = DFS(nb, a, c);
            if (ret) return ret;
        }
        else {
            seen_parent = 1;
        }
    }

    dfs.pop_back();
    return 0;
}

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        a[i] = vis[i] = 0;
        nbs[i].clear();
    }
}

void solve() {
    cin >> N;
    DSU dsu = DSU(N);
    for (int i = 1; i <= N; i++) cin >> a[i];
    int comps = N;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        nbs[a[i]].pb(n);
        nbs[n].pb(a[i]);

        comps -= dsu.combine(a[i], n);
    }

    ll ans = 1;
    for (int i = 1; i <= N; i++) if (!vis[dsu.root(i)]) {
        int ret = DFS(i, 0, i);
        if (ret == 0) ans = 0;
        else if (ret == 1) ans = (ans * N) % MOD;
        else ans = (ans * 2) % MOD;
        dfs.clear();

        vis[dsu.root(i)] = 1;
    }
    cout << ans << endl;
    // cout << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 