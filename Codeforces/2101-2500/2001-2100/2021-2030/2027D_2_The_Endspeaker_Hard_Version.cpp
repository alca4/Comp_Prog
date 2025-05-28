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
ll LINF = 2000000000;
ll MOD = 1000000007;

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
int a[MAXN], b[MAXN];
vector<pll> dp[MAXN];
vector<int> jumperwho[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) a[i] = 0;
    for (int i = 1; i <= M; i++) b[i] = 0;
    for (int i = 0; i <= N; i++) {
        dp[i].clear();
        jumperwho[i].clear();
    }
}

void combine(pll& a, pll b) {
    if (a.FF == b.FF) a = pll(a.FF, add(a.SS, b.SS));
    if (a.FF > b.FF) a = b;
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= M; i++) cin >> b[i];

    for (int i = 0; i <= N; i++) {
        dp[i].resize(M + 1);
        jumperwho[i].resize(M + 1);

        for (int j = 1; j <= M; j++) dp[i][j] = pll(LINF, LINF);
    }

    for (int j = 1; j <= M; j++) {
        int sum = 0;
        int l = 0;
        for (int i = 1; i <= N; i++) {
            sum += a[i];
            while (sum > b[j]) {
                l++;
                sum -= a[l];
            }
            jumperwho[i][j] = l;
        }
    }

    for (int i = 1; i <= M; i++) dp[0][i] = pll(0, 1);
    for (int j = 1; j <= M; j++) {
        int sum = 0;
        int l = 0;
        int r = 0;
        for (int i = 1; i <= N; i++) {
            while (r < i && dp[r][j].FF <= dp[jumperwho[i][j]][j].FF) {
                addeq(sum, dp[r][j].SS);
                r++;
            }
            while (l < jumperwho[i][j]) {
                subeq(sum, dp[l][j].SS);
                l++;
            }

            dp[i][j] = pll(dp[jumperwho[i][j]][j].FF + M - j, sum);

            if (j > 1) combine(dp[i][j], dp[i][j - 1]);
        }
    }

    if (dp[N][M].FF == LINF) cout << -1 << endl;
    else cout << dp[N][M].FF << " " << dp[N][M].SS << endl;

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