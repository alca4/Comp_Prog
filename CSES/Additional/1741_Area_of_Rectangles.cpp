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

const int MAXN = 2000010;
int N;

#define DELTA 1000000

struct ST {
    pll seg[4 * MAXN];
    ll lazy[4 * MAXN];

    void build(int cid, int ss, int se) {
        seg[cid].SS = se - ss + 1;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        build(cid * 2, ss, mid);
        build(cid * 2 + 1, mid + 1, se);
    }

    void apply(ll v, int cid) {
        lazy[cid] += v;
        seg[cid].FF += v;
    }

    void push(int cid, int ss, int se) {
        if (lazy[cid] && ss != se) {
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

        if (seg[cid * 2].FF < seg[cid * 2 + 1].FF) seg[cid] = seg[cid * 2];
        else if (seg[cid * 2 + 1].FF < seg[cid * 2].FF) seg[cid] = seg[cid * 2 + 1];
        else seg[cid] = {seg[cid * 2].FF, seg[cid * 2].SS + seg[cid * 2 + 1].SS};
    }

    ll query(int cid, int ss, int se) {
        if (seg[cid].FF) return se - ss + 1;
        else return se - ss + 1 - seg[cid].SS;
    }

    void clear(int cid, int ss, int se) {
        seg[cid].FF = seg[cid].SS = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST st;

vector<pii> up[MAXN];
vector<pii> down[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        up[x1 + DELTA].pb({y1 + DELTA, y2 + DELTA - 1});
        down[x2 + DELTA - 1].pb({y1 + DELTA, y2 + DELTA - 1});
    }

    st.build(1, 0, 2000000);

    ll area = 0;
    for (int i = 0; i <= 2000000; i++) {
        for (pii p : up[i]) st.update(p.FF, p.SS, 1, 1, 0, 2000000);
        ll d = st.query(1, 0, 2000000);
        area += d;
        for (pii p : down[i]) st.update(p.FF, p.SS, -1, 1, 0, 2000000);
    }
    cout << area << endl;

    return 0;
} 