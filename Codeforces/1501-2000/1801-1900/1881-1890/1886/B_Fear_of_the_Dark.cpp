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

const int MAXN = 0;
int N;
ld a1, a2;
ld b1, b2;
ld p1, p2;

ld dist(ld a, ld b, ld c, ld d) {
    return sqrt((c - a) * (c - a) + (d - b) * (d - b));
}

void solve() {
    cin >> p1 >> p2 >> a1 >> a2 >> b1 >> b2;

    ld lb = 0, ub = 1e6;
    ld ans = 0.0;
    while (ub - lb > EPS) {
        ld w = (lb + ub) / 2;

        int ok = 0;
        if (dist(a1, a2, p1, p2) <= w && dist(a1, a2, 0, 0) <= w) ok = 1;
        if (dist(b1, b2, p1, p2) <= w && dist(b1, b2, 0, 0) <= w) ok = 1;
        if (dist(b1, b2, p1, p2) <= w && dist(a1, a2, 0, 0) <= w && dist(a1, a2, b1, b2) <= w * 2) ok = 1;
        if (dist(a1, a2, p1, p2) <= w && dist(b1, b2, 0, 0) <= w && dist(a1, a2, b1, b2) <= w * 2) ok = 1;

        if (ok) {
            ans = w;
            ub = w - EPS;
        }
        else lb = w + EPS;
    }

    cout << fixed << setprecision(6) << ans << endl;
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
    while (T--) solve();

    return 0;
} 