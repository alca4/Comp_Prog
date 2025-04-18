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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 200010;
int N;
string str;
int arr[MAXN];
ll dp[MAXN][5][2];
ll pow10[5] = {1, 10, 100, 1000, 10000};

void solve() {
    cin >> str;
    N = str.length();
    for (int i = 0; i < N; i++) arr[i + 1] = str[i] - 'A';

    for (int i = 1; i <= N + 1; i++) for (int j = 0; j < 5; j++) 
        dp[i][j][0] = dp[i][j][1] = -LINF;
    dp[N + 1][0][0] = 0;
    for (int i = N; i >= 1; i--) {
        for (int j = 0; j < 5; j++) {
            if (arr[i] < j) {
                dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][0] - pow10[arr[i]]);
                dp[i][j][1] = max(dp[i][j][1], dp[i + 1][j][1] - pow10[arr[i]]);
            }
            else if (arr[i] == j) {
                dp[i][j][0] = max(dp[i][j][0], dp[i + 1][j][0] + pow10[arr[i]]);
                dp[i][j][1] = max(dp[i][j][1], dp[i + 1][j][1] + pow10[arr[i]]);
            }
            else {
                dp[i][arr[i]][0] = max(dp[i][arr[i]][0], dp[i + 1][j][0] + pow10[arr[i]]);
                dp[i][arr[i]][1] = max(dp[i][arr[i]][1], dp[i + 1][j][1] + pow10[arr[i]]);
            }
            
            for (int k = 0; k < 5; k++) if (k != arr[i]) {
                if (k >= j) dp[i][k][1] = max(dp[i][k][1], dp[i + 1][j][0] + pow10[k]);
                else dp[i][j][1] = max(dp[i][j][1], dp[i + 1][j][0] - pow10[k]);
            }
        }
    }

    ll ans = -LINF;
    for (int i = 0; i < 5; i++) ans = max({ans, dp[1][i][0], dp[1][i][1]});
    cout << ans << endl;

    for (int i = 1; i <= N + 1; i++) for (int j = 0; j < 5; j++)
        dp[i][j][0] = dp[i][j][1] = 0;
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 