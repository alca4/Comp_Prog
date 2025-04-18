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

const int MAXN = 200010;
ll N;
ll a[MAXN], b[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        a[n] = i;
    }
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        b[n] = i;
    }

    for (int i = 1; i <= N; i++) if (a[i] > b[i]) swap(a[i], b[i]);

    ll l = a[1], r = b[1];
    ll ans = (l - 1) * (l) / 2  + (r - 1 - l) * (r - l) / 2 +
             (N - r) * (N - r + 1) / 2;
    
    for (int i = 2; i <= N; i++) {
        l = min(l, a[i - 1]);
        r = max(r, b[i - 1]);

        if ((l <= a[i] && a[i] <= r) ||
            (l <= b[i] && b[i] <= r)) continue;
        
        if (b[i] < l) ans += (l - b[i]) * (N - r + 1);
        if (a[i] > r) ans += (a[i] - r) * l;
        if (a[i] < l && r < b[i]) ans += (b[i] - r) * (l - a[i]);
    }

    cout << ans + 1 << endl;

    return 0;
} 