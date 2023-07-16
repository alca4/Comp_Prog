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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 0;
int N;

struct ST {
    vector<ll> seg, lc, rc;

    ST() {
        create();
    }

    int create() {
        seg.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return seg.size() - 1;
    }

    void update(int a, ll v, int cid, ll ss, ll se) {
        int nn = cid;
        if (ss == se) {
            seg[nn] = v;
            return;
        }

        ll mid = (ss + se) / 2;
        if (a <= mid) {
            if (lc[nn] == -1) lc[nn] = create();
            update(a, v, lc[nn], ss, mid);
        }
        else {
            if (rc[nn] == -1) rc[nn] = create();
            update(a, v, rc[nn], mid + 1, se);
        }

        seg[nn] = 0;
        if (lc[nn] != -1) {
            seg[nn] += seg[lc[nn]];
        }
        if (rc[nn] != -1) {
            seg[nn] += seg[rc[nn]];
        }
        return;
    }

    ll query(int a, int b, int cid, ll ss, ll se) {
        if (a <= ss && se <= b) return seg[cid];

        ll mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid && lc[cid] != -1) {
            ans += query(a, b, lc[cid], ss, mid);
        }
        if (b > mid && rc[cid] != -1) {
            ans += query(a, b, rc[cid], mid + 1, se);
        }

        return ans;
    }

    ll walk(int a, int cid, ll ss, ll se) {
        if (ss == se) return ss;

        ll mid = (ss + se) / 2;
        if (lc[cid] != -1 && seg[lc[cid]] >= a)
            return walk(a, lc[cid], ss, mid);
        if (rc[cid] != -1) {
            int w = (lc[cid] == -1 ? 0 : seg[lc[cid]]);
            if (seg[rc[cid]] >= a - w) return walk(a - w, rc[cid], mid + 1, se);
        }
        return -1;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST st;

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    while (N--) {
        char c;
        int n;
        cin >> c >> n;
        if (c == 'I') {
            st.update(n + INF, 1, 0, 0, 2 * INF);
        }
        if (c == 'D') {
            st.update(n + INF, 0, 0, 0, 2 * INF);
        }
        if (c == 'C') {
            cout << st.query(0, n + INF - 1, 0, 0, 2 * INF) << endl;
        }
        if (c == 'K') {
            int w = st.walk(n, 0, 0, 2 * INF);
            if (w == -1) cout << "invalid" << endl;
            else cout << w - INF << endl;
        }
    }

    return 0;
} 