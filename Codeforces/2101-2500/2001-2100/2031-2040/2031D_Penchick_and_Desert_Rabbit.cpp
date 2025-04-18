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

struct ST {
    struct Node {
        ll sum;
        ll minv;
        ll maxv;

        Node() {
            sum = 0;
            minv = LINF;
            maxv = -LINF;
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void addToNode(Node& a, ll v) {
        a.sum += v;
        a.minv += v;
        a.maxv += v;
    }

    void setNode(Node& a, ll v) {
        a.sum = v;
        a.minv = v;
        a.maxv = v;
    }

    void merge(Node& a, Node& b, Node& c) {
        a.sum = b.sum + c.sum;
        a.minv = min(b.minv, c.minv);
        a.maxv = max(b.maxv, c.maxv);
    }

    void set(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            setNode(seg[cid], v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
        merge(seg[cid], seg[cid * 2], seg[cid * 2 + 1]);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            addToNode(seg[cid], v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        merge(seg[cid], seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        Node ans;
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            merge(ans, ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            merge(ans, ans, rans);
        }
        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = Node();
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

const int MAXN = 500010;
int N;
int ans[MAXN];

void solve() {
    cin >> N;
    ST st(N);
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        st.set(i, n, 1, 1, N);
    }

    int last_reachable = N;
    for (int i = N; i >= 1; i--) {
        int prefmax = st.query(1, i, 1, 1, N).maxv;
        if (prefmax <= st.query(i + 1, last_reachable, 1, 1, N).minv) {
            ans[i] = prefmax;
            last_reachable = i;
        }
        else ans[i] = ans[last_reachable];
    }
    
    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;

    for (int i = 1; i <= N; i++) ans[i] = 0;
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