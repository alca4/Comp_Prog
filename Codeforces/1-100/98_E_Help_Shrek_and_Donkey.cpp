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

const int MAXN = 1010;
int M, N;

ld dp[MAXN][MAXN];

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> M >> N;
    for (int i = 0; i <= 1000; i++) dp[0][i] = (ld) 1.0 / (i + 1);
    for (int i = 0; i <= 1000; i++) dp[i][0] = 1;

    for (int s = 2; s <= 2000; s++) for (int m = 1; m <= 1000; m++) {
        if (s - m < 1 || s - m > 1000) continue;
        int n = s - m;
        ld a = (ld) 1.0 * n / (n + 1) * (1 - dp[n - 1][m]);
        ld b = (ld) 1.0 / (n + 1) + a;
        ld c = (ld) 1.0;
        ld d = (ld) 1.0 - dp[n][m - 1];
        ld p = (c - d) / (-a + b + c - d);

        dp[m][n] = max((ld) 1.0 / (n + 1), p * a + (1 - p) * c);
    }

    cout << fixed << setprecision(9) << dp[M][N] << " " << (ld) 1.0 - dp[M][N] << endl;

    return 0;
} 