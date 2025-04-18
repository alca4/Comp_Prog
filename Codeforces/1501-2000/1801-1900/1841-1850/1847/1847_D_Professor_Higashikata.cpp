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

const int MAXN = 200010;
int N, M, Q;
int arr[MAXN];
pii order[MAXN];
int loc[MAXN];

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN], order[4 * MAXN];

    void apply(ll v, int o, int cid) {
        lazy[cid] += v;
        seg[cid] += v;
        if (o) order[cid] = o;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            apply(lazy[cid], order[cid], cid * 2);
            apply(lazy[cid], order[cid], cid * 2 + 1);
        }
        lazy[cid] = order[cid] = 0;
    }

    void update(int a, int b, ll v, int o, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            seg[cid] = v * (se - ss + 1);
            lazy[cid] = v;
            order[cid] = o;
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, o, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, o, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a > b) return 0;
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }

    ll qorder(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return order[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) return qorder(a, b, cid * 2, ss, mid);
        else return qorder(a, b, cid * 2 + 1, mid + 1, se);
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST st, st2;
pii itvs[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;
    int ones = 0;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        arr[i] = c - '0';
        ones += arr[i];
    }
    for (int i = 1; i <= M; i++) {
        cin >> itvs[i].FF >> itvs[i].SS;
    }

    for (int i = M; i >= 1; i--) {
        st.update(itvs[i].FF, itvs[i].SS, 1, i, 1, 1, N);
    }

    int rel = 0,no = 0;
    for (int i = 1; i <= N; i++) {
        int o = st.qorder(i, i, 1, 1, N);
        if (o) {
            order[i] = pii(o, i);
            rel++;
            if (arr[i]) no++;
        }
        else order[i] = pii(INF, i);
    }

    sort(order + 1, order + 1 + N);

    for (int i = 1; i <= N; i++) loc[order[i].SS] = i;

    int have = 0;
    for (int j = 1; j <= rel; j++) st2.update(j, j, arr[order[j].SS], 0, 1, 1, rel);

    while (Q--) {
        int i;
        cin >> i;

        int delta = (arr[i] ? -1 : 1);
        arr[i] = 1 - arr[i];

        ones += delta;
        if (st.qorder(i, i, 1, 1, N)) {
            st2.update(loc[i], loc[i], arr[i], 0, 1, 1, rel);
            if (i <= arr[order[no].SS]) have += delta;
            no += delta;
            if (delta > 0) have += arr[order[ones].SS];
            else have -= arr[order[no + 1].SS];
        }
        // cout << min(ones, rel) - no + no - have << endl;
        if (ones >= rel) cout << rel - no << endl;
        else cout << ones - st2.query(1, ones, 1, 1, rel) << endl;
    }

    return 0;
} 