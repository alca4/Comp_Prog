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

const int MAXN = 300010;
int N;
int arr[MAXN];

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

    void apply(ll v, int cid) {
        lazy[cid] += v;
        seg[cid] += v;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid) ans = max(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = max(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST s1, s2;

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) {
        s1.update(i, i, arr[i], 1, 1, N);
        s1.update(i, i, i - 1, 1, 1, N);
        s2.update(i, i, arr[i], 1, 1, N);
        s2.update(i, i, i - 1, 1, 1, N);
    }

    ll ans = LINF;
    for (int i = 1; i <= N; i++) {
        // for (int j = 1; j <= N; j++) cout << s1.query(j, j, 1, 1, N) << " ";
        // cout << endl;
        // for (int j = 1; j <= N; j++) cout << s2.query(j, j, 1, 1, N) << " ";
        // cout << endl;
        ans = min(ans, max(s2.query(1, N, 1, 1, N), s1.query(1, N, 1, 1, N)));
        if (i < N) s1.update(i + 1, N, -1, 1, 1, N);
        s1.update(i, i, N - i, 1, 1, N);
        s2.update(1, i, 1, 1, 1, N);
        if (i < N) s2.update(i + 1, i + 1, -i, 1, 1, N);
    }

    cout << ans << endl;
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