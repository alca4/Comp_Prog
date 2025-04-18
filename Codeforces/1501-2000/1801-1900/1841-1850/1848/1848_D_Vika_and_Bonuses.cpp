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

const int MAXN = 0;
ll N, K;

ll at(int d) {
    if (K % 10 == 0) return K * (N - d);
    ll K2 = (K + 1ll * (d / 4) * 20);
    int tk = K % 10;
    for (int j = 0; j < (d % 4); j++) {
        K2 += tk;
        tk = (tk * 2) % 10;
    }
    return K2 * (N - d);
}

ll test(int d) {
    ll best = 0;
    for (int i = max(0, d - 3); i <= min((int) N, d + 3); i++) 
        best = max(best, at(i));
    return best;
}

void solve() {
    cin >> K >> N;

    ll tmp = K * N;

    K += K % 10;
    N--;

    int ans = 0;
    int l = 0, r = N / 4;
    while (l <= r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if (test(m1 * 4) <= test(m2 * 4)) {
            l = m1 + 1;
            ans = m1 * 4;
        }
        else {
            r = m2 - 1;
            ans = m2 * 4;
        }
    }

    // ll tans = 0;
    // for (int i = 300000000; i <= 600000000; i++) tans = max(tans, at(i));
    // cout << tans << endl;

    if (tmp > test(ans)) cout << tmp << endl;
    else cout << test(ans) << endl;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 