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

const int MAXN = 20;
int N;
int arr[MAXN];
pii dp[MAXN][MAXN];
vector<pii> ops;

void step(int l, int r) {
    if (l == r) {
        assert(arr[l] != 0);
        ops.pb(pii(l, l));
        arr[l] = 0;
        return;
    }

    step(l, r - 1);
    if (arr[r] != r - l) {
        ops.pb(pii(l, r));

        int v = arr[r - 1] + 1;
        for (int i = l; i <= r; i++) arr[i] = v;

        step(l, r - 1);
    }
    // cout << "stepping " << l << " " << r << endl;
    // for (int i = l; i <= r; i++) cout << arr[i] << " ";
    // cout << endl;
}

void gen_ops(int l, int r) {
    if (l == r) return;

    step(l, r);
    ops.pb(pii(l, r));

    int v = arr[r] + 1;
    for (int i = l; i <= r; i++) arr[i] = v;

    // cout << "patching " << l << " " << r << endl;
    // for (int i = l; i <= r; i++) cout << arr[i] << " ";
    // cout << endl;
}

void backward(int l, int r) {
    if (l == r) return;
    int k = dp[l][r].SS;

    if (k == 0) gen_ops(l, r);
    else {
        backward(l, k);
        backward(k + 1, r);
    }
}

void reset_tc() {
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) if (!arr[i]) {
        arr[i] = 1;
        ops.pb(pii(i, i));
    }
    for (int i = 1; i <= N; i++) dp[i][i].FF = arr[i];

    for (int l = 2; l <= N; l++) {
        for (int i = 1; i + l - 1 <= N; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                dp[i][j].FF = max(dp[i][j].FF, dp[i][k].FF + dp[k + 1][j].FF);
                if (dp[i][j].FF == dp[i][k].FF + dp[k + 1][j].FF) dp[i][j].SS = k;
            }

            if (dp[i][j].FF < (j - i + 1) * (j - i + 1)) 
                dp[i][j] = pii((j - i + 1) * (j - i + 1), 0);
        }
    }

    cout << dp[1][N].FF << " ";
    backward(1, N);

    cout << ops.size() << endl;
    for (pii p : ops) cout << p.FF << " " << p.SS << endl;

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