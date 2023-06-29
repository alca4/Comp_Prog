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
ll MOD = LINF;

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

    for (int i = 0; i < 16; i++) {
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
int N;

int cipolla(int n) {
    n %= MOD;
    if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
    ll a = 2;
    for (; a < MOD; a++) {
        if (power(sub(mult(a, a), n), (MOD - 1) / 2) == MOD - 1) break;
    }

    pll m = pll(a, 1);
    pll ans = pll(1, 0);

    int b = (MOD + 1) / 2;

    for (int i = 0; i < 32; i++) {
        if (b & 1) {
            ans = pll(add(mult(ans.FF, m.FF), mult(mult(ans.SS, m.SS), sub(mult(a, a), n))),
                      add(mult(ans.FF, m.SS), mult(ans.SS, m.FF)));
        }
        m = pll(add(mult(m.FF, m.FF), mult(mult(m.SS, m.SS), sub(mult(a, a), n))),
                add(mult(m.FF, m.SS), mult(m.SS, m.FF)));
        b >>= 1;
    }

    return (ans.FF + MOD) % MOD;
}

void solve() {
    int a, b;
    cin >> a >> b;
    if (b == 2) {
        cout << 1 << endl;
        return;
    }
    MOD = b;
    int r = cipolla(a);
    if (r == -1) cout << "No root" << endl;
    else if (r < (b - r)) cout << r << " " << b - r << endl;
    else cout << b - r << " " << r << endl;
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

    // int p = 17389;
    // MOD = p;
    // for (int i = 1; i < p; i++) {
    //     int r = cipolla(i);
    //     if (r >= 0) assert(mult(r, r) == i);
    // }

    return 0;
} 