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

const int MAXN = 500010;
int N;
ll arr[MAXN];
vector<int> nbs[MAXN];
ll dp[MAXN][2];

void DP(int a, int p) {
    vector<ll> vs;
    for (int nb : nbs[a]) if (nb != p) {
        DP(nb, a);
        vs.pb(dp[nb][1]);
    }

    sort(vs.rbegin(), vs.rend());

    // is not root
    ll t = 0;
    for (int i = 2; i < vs.size(); i++) {
        t = max(t, t + vs[i]);
    }

    if (vs.size() >= 0) dp[a][1] = max(dp[a][1], arr[a]);
    if (vs.size() >= 1) dp[a][1] = max(dp[a][1], vs[0]);
    if (vs.size() >= 2) dp[a][1] = max(dp[a][1], vs[0] + vs[1] + t + arr[a]);

    // is root
    t = 0;
    for (int i = 3; i < vs.size(); i++) {
        t = max(t, t + vs[i]);
    }

    if (vs.size() >= 0) dp[a][0] = max(dp[a][0], arr[a]);
    if (vs.size() >= 1) dp[a][0] = max(dp[a][0], vs[0] + arr[a]);
    if (vs.size() >= 2) dp[a][0] = max(dp[a][0], vs[0] + vs[1]);
    if (vs.size() >= 3) dp[a][0] = max(dp[a][0], vs[0] + vs[1] + vs[2] + t + arr[a]);

    // cout << a << ": " << dp[a][0] << " " << dp[a][1] << endl;
}

ll DP2(int a, int p) {
    ll ans = -LINF;
    for (int nb : nbs[a]) if (nb != p) ans = max(ans, DP2(nb, a));

    ans = max(ans, dp[a][0]);

    // cout << "ans of " << a << " is: " << ans << endl;

    return ans;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) dp[i][0] = dp[i][1] = -LINF;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DP(1, 0);
    cout << max(0ll, DP2(1, 0)) << endl;

    for (int i = 1; i <= N; i++) {
        arr[i] = dp[i][0] = dp[i][1] = 0;
        nbs[i].clear();
    }
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