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
// #define endl "\n"
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

const int MAXN = 100010;
int N;
int should_be[MAXN];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) should_be[i] = -1;

    should_be[1] = 0;
    for (int i = 1; i < N; i++) {
        cout << "? " << i << " " << i + 1 << endl;
        int res;
        cin >> res;

        if (res == 1) should_be[i + 1] = should_be[i];
        else should_be[i + 1] = 1 - should_be[i];
    }

    int lb = 1, ub = N;
    while (ub - lb >= 2) {
        int mid = (lb + ub) / 2;
        
        cout << "? " << 1 << " " << mid << endl;
        int res;
        cin >> res;
        
        if (res != should_be[mid]) lb = mid;
        else ub = mid;
    }

    // if lb = ub, then remaining corrupt could be 1, N - 1, or N

    cout << "? " << 1 << " " << lb << endl;
    int res1;
    cin >> res1;

    cout << "? " << lb << " " << 1 << endl;
    int res2;
    cin >> res2;
    
    if (res1 == res2) cout << "! " << ub << endl;
    else {
        cout << "? " << 1 << " " << ub << endl;
        cin >> res1;

        cout << "? " << ub << " " << 1 << endl;
        cin >> res2;

        if (res1 == res2) cout << "! " << lb << endl;
        else cout << "! " << 1 << endl;
    }

    for (int i = 1; i <= N; i++) should_be[i] = 0;
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