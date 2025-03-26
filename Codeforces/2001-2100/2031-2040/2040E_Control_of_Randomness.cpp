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
ll MOD = 998244353;

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

const int MAXN = 2010;
int N, Q;
vector<int> nbs[MAXN];
ll dp[MAXN][MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        for (int j = 0; j <= N; j++) dp[i][j] = 0;
    }
}

void DP(int a, int p, int p2) {
    if (p == 1) {
        for (int i = 0; i <= N; i++) dp[a][i] = 1;
    }
    else if (a != 1) {
        ll go_back = divide(1, (int) nbs[p].size());
        // cout << a << " " << advance << " " << (int) nbs[p].size() << endl;}

        ll ratio = divide(2, ((int) nbs[p].size() * ((go_back * go_back) % MOD)) % MOD);

        for (int i = 0; i <= N; i++) {
            dp[a][i] = (dp[p2][i] + ratio);
            if (dp[a][i] > MOD) dp[a][i] -= MOD;

            ll tv = dp[p2][i - 1] + 2;
            if (tv > MOD) tv -= MOD;
            if (i > 0) dp[a][i] = min({dp[a][i], tv, dp[a][i - 1]});
        }
        
        /*
        dp[a][i] (1 - (2 / nbs[p].size() - 1) * (go_back / (1 - go_back)^2))))
        */
    }
    for (int nb : nbs[a]) if (nb != p) DP(nb, a, p);
}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DP(1, 0, 0);

    while (Q--) {
        int a, b;
        cin >> a >> b;
        cout << dp[a][b] << endl;
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