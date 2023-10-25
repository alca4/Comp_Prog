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

const int MAXN = 5010;
int N;
ld arr[MAXN];

struct Point {
    int x, y, z;
};

ld dist(const Point& v1, const Point& v2) {
    ld dx = v1.x - v2.x;
    ld dy = v1.y - v2.y;
    ld dz = v1.z - v2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

ld area(ld s1, ld s2, ld s3) {
    ld s = (s1 + s2 + s3) / 2;
    return sqrt(s * (s - s1) * (s - s2) * (s - s3));
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        Point v1, v2, v3;
        cin >> v1.x >> v1.y >> v1.z;
        cin >> v2.x >> v2.y >> v2.z;
        cin >> v3.x >> v3.y >> v3.z;
        ld a = INF;
        arr[i] = area(dist(v1, v2), dist(v1, v3), dist(v2, v3));
    }

    ld diff = LINF;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) if (i != j)
        diff = min(diff, abs(arr[i] - arr[j]));
    
    cout << fixed << setprecision(5) << diff << endl;
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