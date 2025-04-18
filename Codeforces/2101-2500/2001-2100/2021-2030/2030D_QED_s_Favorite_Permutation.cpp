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
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;
        ll lazy = 0;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void apply(int cid, ll v, int ss, int se) {
        seg[cid].lazy += v;
        seg[cid].sum += v * (se - ss + 1);
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void push(int cid, int ss, int se) {
        if (seg[cid].lazy && ss != se) {
            int mid = (ss + se) / 2;
            apply(cid * 2, seg[cid].lazy, ss, mid);
            apply(cid * 2 + 1, seg[cid].lazy, mid + 1, se);
        }
        seg[cid].lazy = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            apply(cid, v, ss, se);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF, 0};
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            ans.merge(ans, rans);
        }
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
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

const int MAXN = 200010;
int N, Q;
int arr[MAXN];

void solve() {
    cin >> N >> Q;
    ST st(N);

    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        
        int a = i, b = n;
        if (a > b) swap(a, b);

        st.update(a + 1, b, -1, 1, 1, N);
    }

    for (int i = 1; i <= N; i++) {
        int v = st.query(i, i, 1, 1, N).maxv;
        if (v < -1) st.update(i, i, -1 - v, 1, 1, N);
    }

    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        int n = i;
        if (c == 'R') {
            n++;
            arr[i] = 1;
        }
        else arr[i] = -1;

        st.update(n, n, 1, 1, 1, N);
    }

    while (Q--) {
        int n;
        cin >> n;
        arr[n] *= -1;

        if (arr[n] < 0) {
            st.update(n + 1, n + 1, -1, 1, 1, N);
            st.update(n, n, 1, 1, 1, N);
        }
        else {
            st.update(n + 1, n + 1, 1, 1, 1, N);
            st.update(n, n, -1, 1, 1, N);
        }

        if (st.query(1, N, 1, 1, N).minv >= 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    st.clear(1, 1, N);
    for (int i = 1; i <= N; i++) arr[i] = 0;
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