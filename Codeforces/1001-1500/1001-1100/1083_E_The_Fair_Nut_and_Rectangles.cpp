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
int INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
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

const int MAXN = 1000010;
int N;

struct Rect {
    ll x, y, a;
} arr[MAXN];

bool operator<(const Rect& r1, const Rect& r2) {
    return pll(r1.x, r1.y) < pll(r2.x, r2.y);
}

struct Line {
    ll m, b;

    ll valueAt(int x) {
        return m * x + b;
    }

    ld intersect(const Line& other) {
        return 1.0 * (other.b - b) / (m - other.m);
    }
};

struct Node {
    Line l;
    int lc = -1, rc = -1;
};

struct LichaoTree {
    vector<Node> seg;

    LichaoTree() {
        create({0, 0});
    }

    int create(Line l) {
        seg.pb({l, -1, -1});
        return seg.size() - 1;
    }

    void insert(Line l, int cid, int ss, int se) {
        int mid = (ss + se) / 2;

        bool dl = l.valueAt(ss) > seg[cid].l.valueAt(ss);
        bool dm = l.valueAt(mid) > seg[cid].l.valueAt(mid);

        if (dm) {
            Line temp = l;
            l = seg[cid].l;
            seg[cid].l = temp;
        }

        if (ss == se) return;
        else if (dl != dm) {
            if (seg[cid].lc == -1) seg[cid].lc = create({0, 0});
            insert(l, seg[cid].lc, ss, mid);
        }
        else {
            if (seg[cid].rc == -1) seg[cid].rc = create({0, 0});
            insert(l, seg[cid].rc, mid + 1, se);
        }
    }

    ll query(int a, int cid, int ss, int se) {
        ll ans = seg[cid].l.valueAt(a);
        if (ss == se) return ans;

        ll mid = (ss + se) / 2;
        if (a <= mid && seg[cid].lc >= 0) ans = max(ans, query(a, seg[cid].lc, ss, mid));
        else if (seg[cid].rc >= 0) ans = max(ans, query(a, seg[cid].rc, mid + 1, se));
        return ans;
    }
};

LichaoTree lct;
ll dp[MAXN];

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        ll x, y, a;
        cin >> x >> y >> a;
        arr[i] = {x, y, a};
    }

    sort(arr + 1, arr + 1 + N);

    for (int i = 1; i <= N; i++) {
        dp[i] = lct.query(arr[i].y, 0, 0, INF) + arr[i].x * arr[i].y - arr[i].a;
        lct.insert({-arr[i].x, dp[i]}, 0, 0, INF);
    }

    ll best = 0;
    for (int i = 1; i <= N; i++) best = max(best, dp[i]);
    cout << best << endl;
    return 0;
} 