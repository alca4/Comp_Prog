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

const int MAXN = 500010;
int N, K, Q;
int arr[MAXN];
int need[MAXN];
int pneed[MAXN];
int nneed[MAXN];
ll dpf[MAXN];
ll dpfc[MAXN];
ll dpb[MAXN];

struct ST {
    vector<ll> seg;
    ST() {ST(0);}
    ST(int n) {
        seg.resize(4 * n + 1);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = LINF;
        int mid = (ss + se) / 2;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        return ans;
    }
};

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        need[i] = c - '0';
    }

    deque<pll> mq;
    mq.push_back({0, 0});
    int prev_need = 0;
    for (int i = 1; i <= N + 1; i++) {
        while (!mq.empty() && mq.front().SS < max(i - K, prev_need)) mq.pop_front();
        dpf[i] = mq.front().FF + arr[i];
        dpfc[i] = dpf[i];
        while (!mq.empty() && mq.front().SS < max(i - K + 1, prev_need)) mq.pop_front();
        while (!mq.empty() && mq.back().FF > dpf[i]) mq.pop_back();
        mq.push_back({dpf[i], i});
        pneed[i] = prev_need;
        if (need[i]) prev_need = i;
    }
    mq.clear();

    mq.push_back({0, N + 1});
    prev_need = N + 1;
    for (int i = N; i >= 0; i--) {
        while (!mq.empty() && mq.front().SS > min(prev_need, i + K)) mq.pop_front();
        dpb[i] = mq.front().FF + arr[i];
        while (!mq.empty() && mq.front().SS > min(prev_need, i + K - 1)) mq.pop_front();
        while (!mq.empty() && mq.back().FF > dpb[i]) mq.pop_back();
        mq.push_back({dpb[i], i});
        nneed[i] = prev_need;
        if (need[i]) prev_need = i;
    }
    mq.clear();

    for (int i = 1; i <= N; i++) dpb[i] -= arr[i];

    // for (int i = 0; i <= N + 1; i++) {
    //     cout << dpf[i] + dpb[i] << " ";
    // }
    // cout << endl;

    // for (int i = 0; i <= N + 1; i++) {
    //     cout << dpf[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i <= N + 1; i++) {
    //     cout << dpb[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i <= N + 1; i++) {
    //     cout << dpf[i] + dpb[i] << " ";
    // }
    // cout << endl;

    cin >> Q;
    while (Q--) {
        int n, v;
        cin >> n >> v;

        dpf[n] += v - arr[n];
        // cout << max(n + 1 - K, pneed[n + 1]) << endl;
        for (int i = max(n + 1 - K, pneed[n + 1]); i <= n; i++) {
            while (!mq.empty() && mq.back().FF > dpf[i]) mq.pop_back();
            mq.push_back({dpf[i], i});
        }
        // cout << mq2.front().FF << endl;
        for (int i = n + 1; i <= min(n + K, N + 1); i++) {
            while (!mq.empty() && mq.front().SS < max(i - K, pneed[i])) mq.pop_front();
            dpf[i] = mq.front().FF + arr[i];
            while (!mq.empty() && mq.front().SS < max(i - K + 1, pneed[i])) mq.pop_front();
            while (!mq.empty() && mq.back().FF > dpf[i]) mq.pop_back();
            mq.push_back({dpf[i], i});
        }
        mq.clear();

        // for (int i = 0; i <= N + 1; i++) {
        //     cout << dpf[i] << " ";
        // }
        // cout << endl;
        // for (int i = 0; i <= N + 1; i++) {
        //     cout << dpb[i] << " ";
        // }
        // cout << endl;
        // for (int i = 0; i <= N + 1; i++) {
        //     cout << dpf[i] + dpb[i] << " ";
        // }
        // cout << endl;
        // cout << endl;
        
        ll ans = LINF;
        for (int i = n; i <= min(n + K, N + 1); i++) ans = min(ans, dpf[i] + dpb[i]);
        cout << ans << endl;

        for (int i = n; i <= min(n + K, N + 1); i++) dpf[i] = dpfc[i];

        // cout << "after query" << endl;
        // for (int i = 0; i <= N + 1; i++) {
        //     cout << dpf[i] + dpb[i] << " ";
        // }
        // cout << endl;
    }

    for (int i = 1; i <= N; i++) {
        arr[i] = need[i] = pneed[i] = nneed[i] = 0;
    }
    for (int i = 0; i <= N + 1; i++) dpf[i] = dpfc[i] = dpb[i] = 0;
    // cout << endl;
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
    while (T--) solve();

    return 0;
} 