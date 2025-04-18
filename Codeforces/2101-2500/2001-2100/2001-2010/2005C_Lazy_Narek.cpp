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

const int MAXN = 1010;
int N, M;
string duck[MAXN];
int dp[5][2];
string narek = "narek";

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        duck[i] = '#';
        string tmp;
        cin >> tmp;
        duck[i] += tmp;
    }

    for (int i = 0; i < 5; i++) dp[i][0] = -INF;
    dp[0][0] = 0;

    for (int i = 1; i <= N; i++) {
        for (int k = 0; k < 5; k++) dp[k][1] = dp[k][0];

        for (int k = 0; k < 5; k++) if (dp[k][1] != -INF) {
            int s = 0;
            int c = k;

            for (int j = 1; j <= M; j++) {
                int in_narek = narek.find(duck[i][j]);

                if (in_narek == c) {
                    c = (c + 1) % 5;
                    s++;
                }
                else if (in_narek >= 0) s--;
            }

            dp[c][1] = max(dp[c][1], dp[k][0] + s);
        }

        for (int k = 0; k < 5; k++) dp[k][0] = dp[k][1];
    }

    int ans = 0;
    for (int k = 0; k < 5; k++) ans = max(ans, dp[k][0] - 2 * k);

    cout << ans << endl;

    for (int k = 0; k < 5; k++) dp[k][0] = dp[k][1] = 0;
    for (int i = 1; i <= N; i++) duck[i].clear();
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