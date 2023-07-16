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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 110;
int N, M;

pii arr[MAXN];

bool Comp(const pii& p1, const pii& p2) {
    if (p1.SS >= 0 && p2.SS < 0) return 1;
    if (p1.SS < 0 && p2.SS >= 0) return 0;
    if (p1.SS >= 0 && p2.SS >= 0) return p1.FF < p2.FF;
    if (p1.SS < 0 && p2.SS < 0) {
        return pii(p1.FF + p1.SS, p2.FF) > pii(p2.FF + p2.SS, p2.FF);
    }
    return 0; // should not execute
}

int dp[MAXN][60010];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i].FF >> arr[i].SS;

    sort(arr + 1, arr + 1 + N, Comp);

    // for (int i = 1; i <= N; i++) cout << arr[i].FF << " " << arr[i].SS << endl;

    dp[0][M] = 1;
    for (int i = 1; i <= N; i++) for (int j = 0; j <= 60000; j++) {
        if (dp[i - 1][j]) {
            if (j >= arr[i].FF && 0 <= j + arr[i].SS && j + arr[i].SS <= 60000) {
                dp[i][j + arr[i].SS] = max(dp[i][j + arr[i].SS], dp[i - 1][j] + 1);
            }
            dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
    }

    int best = 0;
    for (int i = 0; i <= 60000; i++) if (dp[N][best] < dp[N][i]) best = i;
    cout << dp[N][best] - 1 << endl;

    return 0;
} 