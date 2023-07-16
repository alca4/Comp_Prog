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
ll MOD = 1000000007;

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

const int MAXN = 1010;

vector<ll> fact, factinv;
vector<vector<int>> stirling;
vector<vector<int>> stirling2;
struct Comb {
    static void get_fact(int x) {
        fact.resize(x + 1);
        factinv.resize(x + 1);
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
    }

    static void gen_stirling2(int i, int j) {
        stirling2.resize(i + 1);
        for (auto& n : stirling2) n.resize(j + 1);
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n == k) stirling2[n][k] = 1;
            if (n && k) 
                stirling2[n][k] = add(stirling2[n - 1][k - 1], mult(k, stirling2[n - 1][k]));
        }
    }

    static ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }

    static ll fallpow(int a, int b) {
        return mult(fact[a], factinv[a - b]);
    }

    static ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};

int N, M;
ll dp[MAXN][MAXN][2][2];
ll ans[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    Comb::get_fact(N);
    dp[0][0][1][0] = 1;
    for (int i = 0; i < N; i++) for (int j = 0; j <= i; j++) {
        addeq(dp[i + 1][j + 1][0][1], dp[i][j][0][0]);
        addeq(dp[i + 1][j + 1][0][1], dp[i][j][1][0]);
        addeq(dp[i + 1][j + 1][1][1], dp[i][j][0][1]);
        addeq(dp[i + 1][j + 1][1][1], dp[i][j][1][1]);

        addeq(dp[i + 1][j + 1][0][0], dp[i][j][0][0]);
        addeq(dp[i + 1][j + 1][1][0], dp[i][j][0][1]);

        addeq(dp[i + 1][j][0][0], dp[i][j][0][0]);
        addeq(dp[i + 1][j][0][0], dp[i][j][1][0]);
        addeq(dp[i + 1][j][1][0], dp[i][j][0][1]);
        addeq(dp[i + 1][j][1][0], dp[i][j][1][1]);
    }

    for (int i = 0; i <= N; i++) {
        addeq(ans[i], dp[N][i][1][0]);
        if (i < N) addeq(ans[i], dp[N][i][0][0]);
        multeq(ans[i], fact[N - i]);
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int j = i + 1; j <= N; j++) {
            subeq(ans[i], mult(ans[j], Comb::choose(j, i)));
        }
    }

    cout << ans[M] << endl;

    return 0;
} 