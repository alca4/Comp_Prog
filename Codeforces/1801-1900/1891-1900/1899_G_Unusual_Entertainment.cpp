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

const int MAXN = 100010;
int N, Q;
vector<int> nbs[MAXN];
int arr[MAXN];

struct PST {
    vector<ll> seg, lc, rc;
    vector<int> roots;

    PST() {
        create();
        roots.pb(0);
    }

    int create() {
        seg.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return seg.size() - 1;
    }

    int update(int a, ll v, int cid, int ss, int se) {
        int nn = create();
        lc[nn] = lc[cid];
        rc[nn] = rc[cid];
        seg[nn] = seg[cid];
        if (ss == se) {
            seg[nn] += v;
            return nn;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) {
            if (lc[nn] == -1) lc[nn] = create();
            lc[nn] = update(a, v, lc[nn], ss, mid);
        }
        else {
            if (rc[nn] == -1) rc[nn] = create();
            rc[nn] = update(a, v, rc[nn], mid + 1, se);
        }

        seg[nn] = 0;
        if (lc[nn] != -1) seg[nn] += seg[lc[nn]];
        if (rc[nn] != -1) seg[nn] += seg[rc[nn]];
        return nn;
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid && lc[cid] != -1) {
            ans += query(a, b, lc[cid], ss, mid);
        }
        if (b > mid && rc[cid] != -1) {
            ans += query(a, b, rc[cid], mid + 1, se);
        }

        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

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

void solve() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }
    for (int i = 1; i <= N; i++) cin >> arr[i];

    PST pst;
    Euler e(N);
    e.tour(1, 0);

    for (int i = 1; i <= N; i++) {
        pst.roots.pb(pst.update(e.in[arr[i]], 1, pst.roots[i - 1], 1, 2 * N));
    }

    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;
        if (pst.query(e.in[x], e.out[x], pst.roots[r], 1, 2 * N) ==
            pst.query(e.in[x], e.out[x], pst.roots[l - 1], 1, 2 * N)) cout << "NO" << endl;
        else cout << "YES" << endl;
    }

    for (int i = 1; i <= N; i++) {
        arr[i] = 0;
        nbs[i].clear();
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