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

#define ll long long
#define ld long double
#define ull unsigned ll

#define endl "\n"
#define EPS 1e-9

#define sz(v) (int) v.size()
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
// #define cout cerr

ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

#define add(a, b) ((a + b) > MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) > 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) ((a * power(b, MOD - 2)) % MOD)

template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 300010;

struct ST {
    struct Node {
        int sum = 0;
        // ll minv = 0;
        // ll maxv = 0;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            // minv = min(b.minv, c.minv);
            // maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST() {ST(0);}
    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void addToNode(int cid, ll v) {
        seg[cid].sum += v;
        // seg[cid].minv += v;
        // seg[cid].maxv += v;
    }

    void setNode(int cid, ll v) {
        seg[cid].sum = v;
        // seg[cid].minv = v;
        // seg[cid].maxv = v;
    }

    void set(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            setNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            addToNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        Node ans = {0};
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

    void clear(int cid, int ss, int se) {
        seg[cid] = Node();
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

int N;
int arr[MAXN];
ST sts[4];

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        arr[i] = c - '0' + arr[i - 1];
    }

    for (int j = 0; j < 4; j++) sts[j] = ST(6 * N);

    // N / 4 > n1 => always win
    // otherwise, only answer for N % 4 == 2 or 3
    // if N % 4 == 2, then N / 4 == n1 
    // if N % 4 == 3, then N / 4 == n1 or n1 - 1

    ll ans = 0;
    sts[0].update(2 * N, 1, 1, 1, 6 * N);
    for (int i = 2; i <= N; i++) {
        ll tans = 0;
        tans += sts[(i + 0) % 4].query(4 * arr[i] - i + 2 * N + 4, 6 * N, 1, 1, 6 * N).sum;
        // cout << tans << " ";
        tans += sts[(i + 3) % 4].query(4 * arr[i] - i + 2 * N + 4, 6 * N, 1, 1, 6 * N).sum;
        // cout << tans << " ";
        tans += sts[(i + 2) % 4].query(4 * arr[i] - i + 2 * N + 0, 6 * N, 1, 1, 6 * N).sum;
        // cout << tans << " ";
        tans += sts[(i + 1) % 4].query(4 * arr[i] - i + 2 * N - 4, 6 * N, 1, 1, 6 * N).sum;
        // cout << 4 * arr[i] - i + 2 * N - 4 << " ";
        // cout << tans << endl;

        sts[(i - 1) % 4].update(4 * arr[i - 1] - (i - 1) + 2 * N, 1, 1, 1, 6 * N);

        ans += tans;
    }

    cout << ans << endl;

    reset_tc();
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