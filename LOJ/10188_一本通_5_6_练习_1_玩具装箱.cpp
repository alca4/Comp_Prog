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
ll INF = 1000000000000000000;
ll LINF = 1000000000000000000;
ll DELTA = 1000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) {
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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

const int MAXN = 50010;
int N;
ll L;
ll arr[MAXN];
ll psum[MAXN];
ll dp[MAXN];
ll a[MAXN], b[MAXN];

// A_i = i + psum_i
// B_i = i + psum_i - 1 - L

struct Line {
    __int128_t m, b;

    __int128_t valueAt(__int128_t x) {
        return m * (x - DELTA) + b;
    }
};

struct Node {
    Line l;
    int lc = -1, rc = -1;
};

struct LichaoTree {
    vector<Node> seg;

    LichaoTree() {
        create({0, LINF});
    }

    int create(Line l) {
        seg.pb({l, -1, -1});
        return seg.size() - 1;
    }

    void insert(Line l, int cid, ll ss, ll se) {
        ll mid = (ss + se) / 2;

        bool dl = l.valueAt(ss) < seg[cid].l.valueAt(ss);
        bool dm = l.valueAt(mid) < seg[cid].l.valueAt(mid);

        if (dm) swap(l, seg[cid].l);

        // cout << "inserting " << l.m << " " << l.b << endl;

        if (ss == se) return;
        else if (dl != dm) {
            if (seg[cid].lc == -1) seg[cid].lc = create(l);
            insert(l, seg[cid].lc, ss, mid);
        }
        else {
            if (seg[cid].rc == -1) seg[cid].rc = create(l);
            insert(l, seg[cid].rc, mid + 1, se);
        }
        // cout << seg[cid].l.m << " " << seg[cid].l.b << " at " << ss << " " << se << endl;
    }

    ll query(ll a, int cid, ll ss, ll se) {
        ll ans = seg[cid].l.valueAt(a);
        if (ss == se) return ans;

        ll mid = (ss + se) / 2;
        if (a <= mid && seg[cid].lc >= 0) {
            // cout << ans << " " << query(a, seg[cid].lc, ss, mid) << endl;
            ll v = query(a, seg[cid].lc, ss, mid);
            // if (v < ans) cout << "better is: " << v << endl;
            ans = min(ans, v);
        }
        else if (seg[cid].rc >= 0) {
            // cout << ans << " " << query(a, seg[cid].rc, mid + 1, se) << endl;
            ll v = query(a, seg[cid].rc, mid + 1, se);
            // if (v < ans) cout << "better is: " << v << endl;
            ans = min(ans, v);
        }
        return ans;
    }
};

LichaoTree lt;

void solve() {
    cin >> N >> L;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) psum[i] = psum[i - 1] + arr[i];
    for (int i = 0; i <= N; i++) a[i] = i + psum[i], b[i] = a[i] - 1 - L;

    vector<pll> lines;
    lines.pb({0, 0});
    lt.insert({0, 0}, 0, 0, INF);
    for (int i = 1; i <= N; i++) {
        // cout << "best line at " << b[i] << " is " << lt.query(b[i] + DELTA, 0, 0, INF) + b[i] * b[i] << endl;
        // cout << i << endl;
        // for (pll p : lines) cout << p.FF << " " << p.SS << endl;
        // cout << b[i] << endl;
        // cout << lt.query(b[i] + DELTA, 0, 0, INF) << endl;
        // cout << endl;
        dp[i] = lt.query(b[i] + DELTA, 0, 0, INF) + b[i] * b[i];
        lt.insert({-2 * a[i], dp[i] + a[i] * a[i]}, 0, 1, INF);
        lines.pb({-2 * a[i], dp[i] + a[i] * a[i]});
    }
    // for (int i = 1; i <= N; i++) cout << dp[i] << endl;
    // cout << endl;
    cout << dp[N] << endl;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc2.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    while (T--) solve();

    return 0;
} 