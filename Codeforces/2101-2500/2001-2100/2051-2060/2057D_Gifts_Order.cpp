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

Tooting Bec
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

struct Node {
    ll minv1 = 0;
    ll maxv1 = 0;
    ll ans1 = 0;
    ll minv2 = 0;
    ll maxv2 = 0;
    ll ans2 = 0;
    ll ans = 0;

    void merge(Node& b, Node& c) {
        minv1 = min(b.minv1, c.minv1);
        maxv1 = max(b.maxv1, c.maxv1);
        ans1 = max({b.ans1, c.ans1, c.maxv1 - b.minv1});

        minv2 = min(b.minv2, c.minv2);
        maxv2 = max(b.maxv2, c.maxv2);
        ans2 = max({b.ans2, c.ans2, b.maxv2 - c.minv2});

        ans = max(ans1, ans2);
    }
};

extern int N;

struct ST {
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void setNode(int cid, ll v1, ll v2, int id) {
        seg[cid].minv1 = v1 - v2;
        seg[cid].maxv1 = v1 - v2;
        seg[cid].ans1 = 0;

        seg[cid].minv2 = v1 + v2;
        seg[cid].maxv2 = v1 + v2;
        seg[cid].ans2 = 0;
    }

    void set(int a, ll v1, ll v2, int cid, int ss, int se) {
        if (ss == se) {
            setNode(cid, v1, v2, ss);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v1, v2, cid * 2, ss, mid);
        else set(a, v1, v2, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF};
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            ans.merge(ans, rans);
        }
        return ans;
    }
};


const int MAXN = 200010;
int N, Q;
ST st = ST(0);

void reset_tc() {
    st = ST(0);
}

void solve() {
    cin >> N >> Q;
    st = ST(N);
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        st.set(i, a, i, 1, 1, N);
    }

    cout << st.query(1, N, 1, 1, N).ans << endl;
    while (Q--) {
        int n, v;
        cin >> n >> v;
        st.set(n, v, n, 1, 1, N);
        cout << st.query(1, N, 1, 1, N).ans << endl;
    }

    reset_tc();
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