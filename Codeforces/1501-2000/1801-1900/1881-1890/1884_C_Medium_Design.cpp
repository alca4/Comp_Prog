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
int N, M;
map<int, int> compress;
pii rngs[MAXN];
vector<int> in[2 * MAXN];
vector<int> out[2 * MAXN];

struct ST
{
    ll sum[8 * MAXN], minv[8 * MAXN], maxv[8 * MAXN];
    ll lazy[8 * MAXN];

    void apply(ll v, int cid) {
        lazy[cid] += v;
        sum[cid] += v;
        maxv[cid] += v;
        minv[cid] += v;
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
        sum[cid] = sum[cid * 2] + sum[cid * 2 + 1];
        minv[cid] = min(minv[cid * 2], minv[cid * 2 + 1]);
        maxv[cid] = max(maxv[cid * 2], maxv[cid * 2 + 1]);
    }

    ll query_min(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return minv[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = LINF;
        if (a <= mid) ans = min(ans, query_min(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query_min(a, b, cid * 2 + 1, mid + 1, se));
        sum[cid] = sum[cid * 2] + sum[cid * 2 + 1];
        minv[cid] = min(minv[cid * 2], minv[cid * 2 + 1]);
        maxv[cid] = max(maxv[cid * 2], maxv[cid * 2 + 1]);
        return ans;
    }

    ll query_max(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return maxv[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = -LINF;
        if (a <= mid) ans = max(ans, query_max(a, b, cid * 2, ss, mid));
        if (b > mid) ans = max(ans, query_max(a, b, cid * 2 + 1, mid + 1, se));
        sum[cid] = sum[cid * 2] + sum[cid * 2 + 1];
        minv[cid] = min(minv[cid * 2], minv[cid * 2 + 1]);
        maxv[cid] = max(maxv[cid * 2], maxv[cid * 2 + 1]);
        return ans;
    }

    void clear(int cid, int ss, int se) {
        sum[cid] = minv[cid] = maxv[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST st;

void solve() {
    cin >> N >> M;
    compress[1]++;
    compress[M]++;
    for (int i = 1; i <= N; i++) {
        cin >> rngs[i].FF >> rngs[i].SS;
        compress[rngs[i].FF] = 1;
        compress[rngs[i].SS] = 1;
    }

    int cnt = 0;
    for (pii n : compress) {
        compress[n.FF] = ++cnt;
    }

    for (int i = 1; i <= N; i++) {
        rngs[i].FF = compress[rngs[i].FF], rngs[i].SS = compress[rngs[i].SS];

        in[rngs[i].FF].pb(rngs[i].SS);
        out[rngs[i].SS].pb(rngs[i].FF);
    }
    
    ll ans = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int n : in[i]) st.update(i, n, 1, 1, 1, cnt);
        ans = max(ans, st.query_max(1, cnt, 1, 1, cnt) - st.query_min(1, cnt, 1, 1, cnt));
        for (int n : out[i]) st.update(n, i, -1, 1, 1, cnt);
    }

    cout << ans << endl;
    st.clear(1, 1, cnt);
    compress.clear();
    for (int i = 1; i <= N; i++) rngs[i] = {0, 0};
    for (int i = 1; i <= cnt; i++) {
        in[i].clear();
        out[i].clear();
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