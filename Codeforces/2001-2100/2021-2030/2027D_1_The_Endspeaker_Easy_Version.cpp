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

const int MAXN = 300010;
int N, M;
int a[MAXN];
ll asum[MAXN];
int b[MAXN];
vector<ll> dp[MAXN];
vector<int> jumperwho[MAXN];

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) asum[i] = asum[i - 1] + a[i];
    for (int i = 1; i <= M; i++) cin >> b[i];

    for (int i = 1; i <= N + 1; i++) {
        dp[i].resize(M + 1);
        jumperwho[i].resize(M + 1);

        for (int j = 1; j <= M; j++) dp[i][j] = LINF;
    }

    for (int j = 1; j <= M; j++) {
        int tmp = 0;
        for (int i = 1; i <= N; i++) {
            while (tmp <= N && asum[tmp] - asum[i - 1] <= b[j]) tmp++;
            jumperwho[i][j] = tmp - i;
        }
    }

    dp[1][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (jumperwho[i][j] > 0) mineq(dp[i + jumperwho[i][j]][j], dp[i][j] + M - j);
            if (j < M) mineq(dp[i][j + 1], dp[i][j]);
            cout << dp[i][j] << endl;
        }
    }

    ll ans = LINF;
    for (int i = 1; i <= M; i++) mineq(ans, dp[N + 1][i]);

    if (ans == LINF) cout << -1 << endl;
    else cout << ans - 1 << endl;

    for (int i = 1; i <= N + 1; i++) dp[i].clear();
    for (int i = 1; i <= N + 1; i++) jumperwho[i].clear();
    for (int i = 1; i <= N; i++) a[i] = b[i] = asum[i] = 0;
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