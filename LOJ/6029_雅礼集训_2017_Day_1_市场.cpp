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
ll INF = 2000000000;
ll LINF = 1000000000000000000;
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

const int MAXN = 100010;
int N, Q;

struct ST {
    ll sum[4 * MAXN], minv[4 * MAXN], maxv[4 * MAXN];
    pll lazy[4 * MAXN];

    void apply(ll v, int cid, int v2) {
        lazy[cid].SS += v;
        sum[cid] += v * v2;
        minv[cid] += v;
        maxv[cid] += v;
    }

    void apply2(ll v, int cid, int v2) {
        lazy[cid].FF = v;
        lazy[cid].SS = 0;
        sum[cid] = v * v2;
        minv[cid] = v;
        maxv[cid] = v;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            int mid = (ss + se) >> 1;
            if (lazy[cid].FF != INF) {
                apply2(lazy[cid].FF, cid << 1, mid - ss + 1);
                apply2(lazy[cid].FF, cid << 1 | 1, se - (mid + 1) + 1);
            }
            if (lazy[cid].SS) {
                int mid = (ss + se) >> 1;
                apply(lazy[cid].SS, cid << 1, mid - ss + 1);
                apply(lazy[cid].SS, cid << 1 | 1, se - (mid + 1) + 1);
            }
        }
        lazy[cid] = {INF, 0};
    }

    void add(int a, int b, ll v, int cid, int ss, int se) {
        if (a <= ss && se <= b) {
            apply(v, cid, se - ss + 1);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) >> 1;
        if (a <= mid) add(a, b, v, cid << 1, ss, mid);
        if (b > mid) add(a, b, v, cid << 1 | 1, mid + 1, se);
        sum[cid] = sum[cid << 1] + sum[cid << 1 | 1];
        minv[cid] = min(minv[cid << 1], minv[cid << 1 | 1]);
        maxv[cid] = max(maxv[cid << 1], maxv[cid << 1 | 1]);
    }

    void divide(int a, int b, ll v, int cid, int ss, int se) {
        if (a <= ss && se <= b) {
            ll minv2;
            if (minv[cid] > 0) minv2 = minv[cid] / v;
            else minv2 = (minv[cid] - v + 1) / v;
            ll maxv2;
            if (maxv[cid] > 0) maxv2 = maxv[cid] / v;
            else maxv2 = (maxv[cid] - v + 1) / v;

            if (minv2 - minv[cid] == maxv2 - maxv[cid]) {
                apply(minv2 - minv[cid], cid, se - ss + 1);
                return;
            }
            // cout << "to " << minv[cid] << endl;
            // cout << "sum is now " << sum[cid] << endl;
        }

        push(cid, ss, se);
        int mid = (ss + se) >> 1;
        if (a <= mid) divide(a, b, v, cid << 1, ss, mid);
        if (b > mid) divide(a, b, v, cid << 1 | 1, mid + 1, se);
        sum[cid] = sum[cid << 1] + sum[cid << 1 | 1];
        minv[cid] = min(minv[cid << 1], minv[cid << 1 | 1]);
        maxv[cid] = max(maxv[cid << 1], maxv[cid << 1 | 1]);
    }

    void update(int a, int v, int cid, int ss, int se) {
        if (ss == se) {
            sum[cid] = minv[cid] = maxv[cid] = v;
            lazy[cid] = {INF, 0};
            return;
        }

        int mid = (ss + se) >> 1;
        if (a <= mid) update(a, v, cid << 1, ss, mid);
        else update(a, v, cid << 1 | 1, mid + 1, se);
        sum[cid] = sum[cid << 1] + sum[cid << 1 | 1];
        minv[cid] = min(minv[cid << 1], minv[cid << 1 | 1]);
        maxv[cid] = max(maxv[cid << 1], maxv[cid << 1 | 1]);
        lazy[cid] = {INF, 0};
    }

    ll querySum(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) {
            return sum[cid];
        }
        if (minv[cid] == maxv[cid]) {
            return minv[cid] * (min(se, b) - max(ss, a) + 1);
        }

        push(cid, ss, se);
        ll ans = 0;
        int mid = (ss + se) >> 1;
        if (a <= mid) ans += querySum(a, b, cid << 1, ss, mid);
        if (b > mid) ans += querySum(a, b, cid << 1 | 1, mid + 1, se);
        return ans;
    } 

    ll queryMin(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return minv[cid];
        if (minv[cid] == maxv[cid]) return minv[cid];

        push(cid, ss, se);
        ll ans = INF;
        int mid = (ss + se) >> 1;
        if (a <= mid) ans = min(ans, queryMin(a, b, cid << 1, ss, mid));
        if (b > mid) ans = min(ans, queryMin(a, b, cid << 1 | 1, mid + 1, se));
        return ans;
    } 
};

ST st;

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        st.update(i, n, 1, 1, N);
    }

    while (Q--) {
        int t, l, r, v;
        cin >> t >> l >> r;
        l++, r++;
        // cout << l << " " << r << endl;
        if (t == 1) {
            cin >> v;
            st.add(l, r, v, 1, 1, N);
        }
        if (t == 2) {
            cin >> v;
            st.divide(l, r, v, 1, 1, N);
        }
        if (t == 3) {
            cout << st.queryMin(l, r, 1, 1, N) << endl;
        }
        if (t == 4) {
            cout << st.querySum(l, r, 1, 1, N) << endl;
        }

        // for (int i = 1; i <= N; i++) cout << st.queryMin(i, i, 1, 1, N) << " ";
        // cout << endl;
    }
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
    // T = "change";
    while (T--) solve();

    return 0;
} 