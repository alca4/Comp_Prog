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

const int MAXN = 200010;

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

int N, M;
vector<pii> nbs[MAXN];
pii edgelist[MAXN];
int vis[MAXN];
int trust[MAXN];
DSU dsu;

void reset_tc() {
    dsu = DSU(0);
    for (int i = 1; i <= M; i++) {
        edgelist[i] = pii(0, 0);
        trust[i] = vis[i] = 0;
    }
    for (int i = 1; i <= N; i++) nbs[i].clear();
}

void solve() {
    cin >> N >> M;
    dsu = DSU(N);
    int guy = 0;
    for (int i = 1; i <= M; i++) {
        cin >> edgelist[i].FF >> edgelist[i].SS;
        nbs[edgelist[i].FF].pb(pii(edgelist[i].SS, i));
        nbs[edgelist[i].SS].pb(pii(edgelist[i].FF, i));
    }

    vector<int> guys;
    set<int> bad;
    for (int i = 1; i <= M; i++) {
        trust[i] = dsu.combine(edgelist[i].FF, edgelist[i].SS);
        if (!trust[i]) {
            bad.insert(edgelist[i].FF);
            bad.insert(edgelist[i].SS);
            guys.pb(i);
            // cout << "no trust " << i << endl;
        }
    }

    if (bad.size() == 3 && guys.size() == 3) {
        // cout << "emergency" << endl;
        queue<int> bfs;
        bfs.push(*bad.begin());
        while (!bfs.empty()) {
            int n = bfs.front();
            bfs.pop();

            if (vis[n]) continue;
            else vis[n] = 1;

            int found = 0;
            for (pii nb : nbs[n]) if (trust[nb.SS]) {
                bfs.push(nb.FF);
                if (!found && bad.count(nb.FF) && !vis[nb.FF]) {
                    found = 1;
                    trust[nb.SS] = 0;

                    for (int guy : guys) {
                        // cout << n << " " << nb.FF << endl;
                        if (edgelist[guy].FF == *bad.begin() && edgelist[guy].SS == nb.FF) trust[guy] = 1;
                        if (edgelist[guy].SS == *bad.begin() && edgelist[guy].FF == nb.FF) trust[guy] = 1;
                    }
                }
            }

            if (found) break;
        }
    }

    for (int i = 1; i <= M; i++) cout << trust[i];
    cout << endl;

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