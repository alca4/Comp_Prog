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

const int MAXN = 110;
const int DELTA = 10000;
int N;
int arr[MAXN];
int dp[MAXN][MAXN * MAXN][2];

void solve() {
    string str;
    cin >> str;
    N = str.length();
    for (int i = 1; i <= N; i++) arr[i] = str[i - 1] - '0';

    int nz = 0;
    for (int i = 1; i <= N; i++) nz += arr[i];
    nz = N - nz;
    
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= (N - 1) * N / 2; j++) dp[i][j][0] = INF;
    }

    dp[0][0][0] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++) for (int k = 0; k <= (N - 1) * N / 2; k++)
            dp[j][k][1] = INF;

        for (int j = 0; j <= N; j++) for (int k = 0; k <= (N - 1) * N / 2; k++)
            if (dp[j][k][0] != INF) {
                if (j < N) 
                    mineq(dp[j + 1][k][1], dp[j][k][0] + arr[i + 1]);
                if (k + j <= (N - 1) * N / 2) 
                    mineq(dp[j][k + j][1], dp[j][k][0] + 1 - arr[i + 1]);
            }
        
        for (int j = 0; j <= N; j++) for (int k = 0; k <= (N - 1) * N / 2; k++)
            dp[j][k][0] = dp[j][k][1];
    }

    int v = (N - 1) * N - (nz - 1) * nz - (N - nz - 1) * (N - nz);
    cout << dp[nz][v / 4][0] / 2 << endl;
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
    while (T--) solve();

    return 0;
} 