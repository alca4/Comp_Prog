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

const int MAXN = 200010;
int N, M;

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

DSU dsu;
vector<pii> uds[11][11];

void solve() {
    cin >> N >> M;

    dsu = DSU(N);

    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        uds[b][a % b].pb(pii(a, c));
    }

    for (int i = 1; i <= 10; i++) for (int j = 0; j < i; j++) sort(uds[i][j].begin(), uds[i][j].end());

    int comps = N;
    for (int i = 1; i <= 10; i++) {
        for (int j = 0; j < i; j++) if (uds[i][j].size()) {
            pii previous = uds[i][j][0];
            for (int k = 1; k < uds[i][j].size(); k++) {
                // cout << "aah" << endl;
                if (previous.FF + i * previous.SS >= uds[i][j][k].FF) {
                    if (previous.FF + i * previous.SS <= uds[i][j][k].FF + i * uds[i][j][k].SS) 
                        previous = {previous.FF, uds[i][j][k].SS + (uds[i][j][k].FF - previous.FF) / i};
                    // cout << previous.FF << " " << previous.SS << endl;
                }
                else {
                    for (int l = 1; l <= previous.SS; l++) comps -= dsu.combine(previous.FF, previous.FF + i * l);
                    previous = uds[i][j][k];
                }
            }

            for (int l = 1; l <= previous.SS; l++) 
                comps -= dsu.combine(previous.FF, previous.FF + i * l);
        }
    }
    
    cout << comps << endl;

    for (int i = 1; i <= 10; i++) for (int j = 0; j < i; j++) uds[i][j].clear();
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