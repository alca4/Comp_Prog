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

#define size(v) (int) v.size()
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
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
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

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;

struct ST {
    struct Node {
        // ll sum = 0;
        ll minv = 0;
        // ll maxv = 0;
        ll lazy = 0;

        void merge(Node& b, Node& c) {
            // sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            // maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void apply(int cid, ll v, int ss, int se) {
        seg[cid].lazy += v;
        // seg[cid].sum += v * (se - ss + 1);
        seg[cid].minv += v;
        // seg[cid].maxv += v;
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
        Node ans = {LINF, 0};
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

int N, M;
int d[MAXN];
vi fbridge[MAXN];
ST st(0);

void reset_tc() {
    st = ST(0);
    for (int i = 1; i <= N; i++) fbridge[i].clear();
    for (int i = 1; i <= N; i++) d[i] = 0;
}

void solve() {
    cin >> N >> M;
    st = ST(N);
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        fbridge[a].pb(b);
    }

    for (int i = 1; i <= N; i++) d[i] = i;

    for (int i = 1; i < N; i++) {
        if (d[i] > d[i - 1] + 1) {
            st.update(i, i, d[i - 1] + 1 - d[i], 1, 1, N);
            d[i] = d[i - 1] + 1;
        }

        cout << (st.query(i, N, 1, 1, N).minv >= 0);
        // for (int j = 1; j <= N; j++) 
        //     cout << st.query(j, j, 1, 1, N).minv << " ";
        // cout << endl;

        for (int n : fbridge[i]) {
            if (d[n] > d[i] + 1) {
                st.update(n, n, d[i] + 1 - d[n], 1, 1, N);
                d[n] = d[i] + 1;
            }
        }

        st.update(i, N, 1, 1, 1, N);
    }
    cout << endl;

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