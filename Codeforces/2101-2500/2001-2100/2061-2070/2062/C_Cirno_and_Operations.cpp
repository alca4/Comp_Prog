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

const int MAXN = 60;
int N;
ll a[MAXN];
ll b[MAXN];
ll c[MAXN];
ll d[MAXN];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];

    if (N > 1) {
        for (int i = 1; i <= N; i++) b[i] = a[N - i + 1];
        for (int i = 1; i < N; i++) b[i] = b[i + 1] - b[i];
    }

    if (N > 2) {
        for (int i = 1; i <= N - 1; i++) c[i] = b[N - 1 - i + 1];
        for (int i = 1; i < N - 1; i++) c[i] = c[i + 1] - c[i];
    }

    if (N > 3) {
        for (int i = 1; i <= N - 2; i++) d[i] = c[N - 2 - i + 1];
        for (int i = 1; i < N - 2; i++) d[i] = d[i + 1] - d[i];
    }

    ll cand = -LINF;
    for (int i = N; i >= 1; i--) {
        ll tsum = 0;
        for (int j = 1; j <= i; j++) tsum += a[j];
        cand = max(cand, tsum);

        for (int j = 1; j < i; j++) {
            a[j] = a[j + 1] - a[j];
        }
    }

    for (int i = N - 1; i >= 1; i--) {
        ll tsum = 0;
        for (int j = 1; j <= i; j++) tsum += b[j];
        cand = max(cand, tsum);

        for (int j = 1; j < i; j++) {
            b[j] = b[j + 1] - b[j];
        }
    }

    for (int i = N - 2; i >= 1; i--) {
        ll tsum = 0;
        for (int j = 1; j <= i; j++) tsum += c[j];
        cand = max(cand, tsum);

        for (int j = 1; j < i; j++) {
            c[j] = c[j + 1] - c[j];
        }
    }

    for (int i = N - 3; i >= 1; i--) {
        ll tsum = 0;
        for (int j = 1; j <= i; j++) tsum += d[j];
        cand = max(cand, tsum);

        for (int j = 1; j < i; j++) {
            d[j] = d[j + 1] - d[j];
        }
    }

    cout << cand << endl;
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