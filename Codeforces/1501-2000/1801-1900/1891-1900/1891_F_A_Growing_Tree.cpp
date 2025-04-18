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

const int MAXN = 500010;
int Q;
vector<int> nbs[MAXN];
vector<pii> ud[MAXN];

struct Euler {
    int T;
    vector<int> in, out, euler;

    Euler() {Euler(0);}
    Euler(int n) {
        T = 0;
        in.resize(n + 1);
        out.resize(n + 1);
        euler.resize(n * 2 + 1);
    }

    void tour(int a, int p) {
        in[a] = ++T;
        euler[T] = a;
        for (int nb : nbs[a]) if (nb != p) tour(nb, a);
        out[a] = ++T;
        euler[T] = -a;
    }
};

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        while (a < arr.size()) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {return query(b) - query(a - 1);}

    void clear() {
        arr.resize(0);
    }
};

void solve() {
    cin >> Q;

    int sz = 1;
    for (int i = 1; i <= Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int v;
            cin >> v;
            sz++;
            nbs[v].pb(sz);
        }
        else {
            int v, x;
            cin >> v >> x;
            ud[sz].pb({v, x});
        }
    }

    Euler e(sz);
    BIT b(2 * sz);
    e.tour(1, 0);
    for (int i = 1; i <= sz; i++) {
        ll v = b.query(e.in[i]);
        b.update(e.in[i], -v);
        if (e.out[i] < 2 * sz) b.update(e.out[i] + 1, v);
        
        for (pii p : ud[i]) {
            b.update(e.in[p.FF], p.SS);
            if (e.out[p.FF] < 2 * sz) b.update(e.out[p.FF] + 1, -p.SS);
        }
        // for (int i = 1; i <= sz; i++) cout << b.query(e.in[i]) << " ";
        // cout << endl;
    }
    for (int i = 1; i <= sz; i++) cout << b.query(e.in[i]) << " ";
    cout << endl;

    for (int i = 1; i <= sz; i++) {
        nbs[i].clear();
        ud[i].clear();
    }
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