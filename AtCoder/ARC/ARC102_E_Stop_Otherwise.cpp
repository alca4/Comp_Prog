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
ll MOD = 998244353;

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

const int MAXN = 2010;
int N, K;

ll fact[1000010], factinv[1000010];

struct Comb {
    static void get_fact(int x) {
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
    }

    static ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }

    static ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};

ll dp[MAXN][MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> K >> N;

    dp[0][N] = 1;
    for (int i = 1; i <= K; i++) for (int j = 0; j <= N; j++) {
        if (j) dp[i][j] = add(dp[i][j], dp[i][j - 1]);
        dp[i][j] = add(dp[i][j], dp[i - 1][j]);
        if (j) dp[i][j] = sub(dp[i][j], dp[i - 1][j - 1]);
        
        dp[i][j] = add(dp[i][j], mult(sub(dp[i - 1][N], dp[i - 1][j]), 2));
    }

    Comb::get_fact(1000000);
    for (int i = 2; i <= 2 * K; i++) {
        int classes = 0;
        int rep = 0;
        for (int j = 1; j <= K; j++) {
            if (1 > i - j || i - j > K) classes++;
            if (j < i - j && (i - j <= K)) rep++;
        }

        ll ans = 0;
        if (rep && classes) {
            for (int t = 0; t <= N; t++) {
                ll v = dp[rep][N - t];
                if (N - t) v = sub(v, dp[rep][N - t - 1]);
                ans = add(ans, mult(v, Comb::stars_bars(N - t, classes)));
            }
        }
        else if (rep) ans = add(ans, dp[rep][0]);
        else ans = add(ans, Comb::stars_bars(N, classes));

        if (i % 2 == 0) {
            if (rep && classes) {
                for (int t = 0; t <= N - 1; t++) {
                    ll v = dp[rep][N - t];
                    if (N - t) v = sub(v, dp[rep][N - t - 1]);
                    ans = add(ans, mult(v, Comb::stars_bars(N - 1 - t, classes)));
                }
            }
            else if (rep) ans = add(ans, sub(dp[rep][1], dp[rep][0]));
            else ans = add(ans, Comb::stars_bars(N - 1, classes));
        }
        cout << ans << endl;
    }

    return 0;
} 