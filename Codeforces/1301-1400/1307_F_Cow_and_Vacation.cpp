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
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

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

const int MAXN = 400010;
int N, K, M, Q;
vector<int> nbs[MAXN];
int col[MAXN];
vector<int> rest;

struct DSU {
    vector<int> p, sz;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    }

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
};

const int MAXPOW2 = 19;

struct LCA {
    vector<int> in, out;
    vector<int> lift[MAXPOW2];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        for (int i = 0; i < MAXPOW2; i++) lift[i].resize(n + 1);
        in[0] = 0;
        out[0] = INF;
        setup_lca();
    }

    void tour(int a, int p) {
        lift[0][a] = p;
        for (int j = 1; j < MAXPOW2; j++) 
            lift[j][a] = lift[j - 1][lift[j - 1][a]];
        in[a] = ++T;
        for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
        out[a] = ++T;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    void setup_lca() {tour(1, 0);}
    int lca(int a, int b) {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = MAXPOW2 - 1; i >= 0; i--) 
            if (!is_anc(lift[i][a], b)) a = lift[i][a];
        
        return lift[0][a];
    }

    int dist(int a, int b) {
        if (a == b) return 0;
        if (is_anc(a, b)) swap(a, b);

        int t = a;
        int d = 0;
        for (int i = MAXPOW2 - 1; i >= 0; i--)
            if (!is_anc(lift[i][t], b)) {
                t = lift[i][t];
                d += (1 << i);
            }
        
        return d + 1;
    }

    int travel(int a, int dist) {
        for (int i = MAXPOW2 - 1; i >= 0; i--) {
            if (dist & (1 << i)) a = lift[i][a];
        }
        return a;
    }
};

void solve() {
    cin >> N >> K >> M;
    int N0 = N;
    for (int i = 1; i < N0; i++) {
        int a, b;
        cin >> a >> b;
        int c = ++N;
        nbs[a].pb(c);
        nbs[c].pb(a);
        nbs[b].pb(c);
        nbs[c].pb(b);
    }

    queue<pii> bfs;
    for (int i = 1; i <= M; i++) {
        int n;
        cin >> n;
        rest.pb(n);
        bfs.push({0, n});
        col[n] = n;
    }

    DSU dsu(N);
    while (!bfs.empty()) {
        pii n = bfs.front();
        bfs.pop();

        if (n.FF < K) {
            for (int nb : nbs[n.SS]) {
                if (!col[nb]) {
                    col[nb] = col[n.SS];
                    bfs.push({n.FF + 1, nb});
                }
                else dsu.combine(col[n.SS], col[nb]);
            }
        }
    }

    for (int i = 1; i <= N; i++) if (col[i]) col[i] = dsu.root(col[i]);

    LCA lca(N);

    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (col[a] && col[a] == col[b]) cout << "YES" << endl;
        else {
            int c = lca.lca(a, b);

            int alca = lca.dist(a, c);
            int blca = lca.dist(b, c);

            if (alca + blca <= 2 * K) cout << "YES" << endl;
            else {
                if (alca > blca) {
                    swap(a, b);
                    swap(alca, blca);
                }

                if (alca < K) a = lca.travel(b, blca - (K - alca));
                else a = lca.travel(a, K);
                b = lca.travel(b, K);

                if (col[a] && col[a] == col[b]) cout << "YES" << endl;
                else cout << "NO" << endl;
            }
        }
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 