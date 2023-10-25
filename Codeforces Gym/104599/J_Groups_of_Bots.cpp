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

const int MAXN = 100010;
int N;
pll arr[MAXN];
set<int> baa;
set<int> baah;

ll get_ans(int a) {
    ll lsum = 0, rsum = 0;
    for (int i = 1; i <= N; i++) {
        if (arr[i].FF < a) lsum += arr[i].SS * (a - arr[i].FF);
        else rsum += arr[i].SS * (arr[i].FF - a);
    }
    return abs(lsum - rsum);
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].FF >> arr[i].SS;
        baa.insert(arr[i].FF - 1);
        baa.insert(arr[i].FF + 1);
        baah.insert(arr[i].FF);
    }
    for (int i = 1; i <= N; i++) {
        baa.erase(arr[i].FF);
    }

    int lb = 0, ub = INF;
    ll ans = LINF;
    while (lb <= ub) {
        int m1 = (ub - lb) / 3 + lb;
        int m2 = ub - (ub - lb) / 3;

        ll a1;
        if (baah.count(m1)) {
            a1 = min(get_ans(*baa.upper_bound(m1)), get_ans(*(--baa.upper_bound(m1))));
        }
        else a1 = get_ans(m1);
        ll a2;
        if (baah.count(m2)) {
            a2 = min(get_ans(*baa.upper_bound(m2)), get_ans(*(--baa.upper_bound(m2))));
        }
        else a2 = get_ans(m2);
        if (a1 < a2) {
            ub = m2 - 1;
        }
        else {
            lb = m1 + 1;
        }
        ans = min({ans, a1, a2});
    }
    cout << ans << endl;
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