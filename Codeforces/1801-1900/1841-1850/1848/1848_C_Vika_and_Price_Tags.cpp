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

const int MAXN = 100010;
int N;
int a[MAXN], b[MAXN];

int hi(int a, int b) {
    if (a % 2 == 1 && b % 2 == 0) return 1;
    else if (a % 2 == 0 && b % 2 == 1) return 2;
    else return 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];

    int ok = 1;
    int t = -1;
    for (int i = 1; i <= N; i++) {
        if (!a[i] && !b[i]) continue;
        // if (a[i] && b[i]) {
            int g = gcd(a[i], b[i]);
            a[i] /= g;
            b[i] /= g;
        // }
        a[i] %= 2;
        b[i] %= 2;
        int v;
        if (a[i] && b[i]) v = 0;
        if (!a[i] && b[i]) v = 1;
        if (a[i] && !b[i]) v = 2;
        if (t != v) {
            if (t == -1) t = v;
            else ok = 0;
        }
        // cout << v << " ";
    }
    // cout << endl;

    int zeros = 0;
    for (int i = 1; i <= N; i++) zeros += (a[i] == 0);
    if (zeros == N) ok = 1;

    zeros = 0;
    for (int i = 1; i <= N; i++) zeros += (b[i] == 0);
    if (zeros == N) ok = 1;

    if (ok) cout << "YES" << endl;
    else cout << "NO" << endl;

    for (int i = 1; i <= N; i++) a[i] = b[i] = 0;
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