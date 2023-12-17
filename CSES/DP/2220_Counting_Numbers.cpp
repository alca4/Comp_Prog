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

const int MAXN = 0;
ll A, B;
int a[20][2];
ll dp[20][10][2][2];

ll solve(int t) {
    for (int i = 0; i <= 19; i++) for (int j = 0; j < 10; j++) 
        dp[i][j][0][0] = dp[i][j][0][1] = dp[i][j][1][0] = dp[i][j][1][1] = 0;
    
    dp[19][0][1][0] = 1;
    for (int i = 18; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (dp[i + 1][k][0][0]) {       // less than value, never started
                    // still won't start
                    if (k == 0 && j == 0) 
                        dp[i][j][0][0] += dp[i + 1][k][0][0];
                    // will start
                    else if (k == 0 && j > 0) 
                        dp[i][j][0][1] += dp[i + 1][k][0][0];
                }

                if (dp[i + 1][k][1][0]) {       // equal to value, never started
                    // still won't start, equal
                    if (k == 0 && j == 0 && a[i][t] == 0)
                        dp[i][j][1][0] += dp[i + 1][k][1][0];
                    // still won't start, now less
                    else if (k == 0 && j == 0 && a[i][t] > 0)
                        dp[i][j][0][0] += dp[i + 1][k][1][0];
                    // start, now less
                    else if (k == 0 && j > 0 && j < a[i][t]) 
                        dp[i][j][0][1] += dp[i + 1][k][1][0];
                    // start, equal
                    else if (k == 0 && j > 0 && j == a[i][t])
                        dp[i][j][1][1] += dp[i + 1][k][1][0];
                }

                if (dp[i + 1][k][0][1]) {        // less than value, started
                    // just needs to be different
                    if (k != j) 
                        dp[i][j][0][1] += dp[i + 1][k][0][1];
                }

                if (dp[i + 1][k][1][1]) {        // equal to value, started
                    // now less than
                    if (k != j && j < a[i][t]) 
                        dp[i][j][0][1] += dp[i + 1][k][1][1];
                    // still equal to
                    if (k != j && j == a[i][t])
                        dp[i][j][1][1] += dp[i + 1][k][1][1];
                }
            }
        }
    }

    ll tot = 0;
    for (int j = 0; j < 10; j++) tot += dp[0][j][0][1] + dp[0][j][1][1];
    return tot;
}

void solve() {
    cin >> A >> B;
    if (A == 0) {
        for (int i = 0; i < 19; i++) {
            a[i][1] = B % 10;
            B /= 10;
        }
        cout << solve(1) + 1 << endl;
    }
    else {
        A--;
        for (int i = 0; i < 19; i++) {
            a[i][0] = A % 10;
            A /= 10;
            a[i][1] = B % 10;
            B /= 10;
        }
        cout << solve(1) - solve(0) << endl;
    }
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