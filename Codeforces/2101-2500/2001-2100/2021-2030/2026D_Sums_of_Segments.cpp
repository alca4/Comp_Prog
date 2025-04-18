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

const int MAXN = 300010;
int N, Q;
ll arr[MAXN];
ll psum[MAXN];
ll ppsumsum[MAXN];
ll bigsum[MAXN];
ll stoppers[MAXN];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) psum[i] = psum[i - 1] + arr[i];
    for (int i = 1; i <= N; i++) ppsumsum[i] = ppsumsum[i - 1] + psum[i];

    for (int i = 1; i <= N; i++) bigsum[1] += psum[i];
    for (int i = 2; i <= N; i++) bigsum[i] = bigsum[i - 1] - arr[i - 1] * (N - i + 2);
    for (int i = 2; i <= N; i++) bigsum[i] += bigsum[i - 1];
    for (int i = 1; i <= N; i++) stoppers[i] = stoppers[i - 1] + N - i + 1;

    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        ll l, r;
        cin >> l >> r;

        int rl = distance(stoppers + 1, upper_bound(stoppers + 1, stoppers + 1 + N, l - 1)) + 1;
        int rr = distance(stoppers + 1, upper_bound(stoppers + 1, stoppers + 1 + N, r - 1)) + 1;

        ll ans = 0;
        if (rl == rr) {
            int lback = l - stoppers[rl - 1];
            int rback = r - stoppers[rr - 1];

            ans += ppsumsum[rl - 1 + rback] - ppsumsum[rl - 2 + lback] - 
                   psum[rl - 1] * (rback - lback + 1);
        }
        else {
            if (rr - 1 >= rl + 1) ans += bigsum[rr - 1] - bigsum[rl];

            int lback = l - stoppers[rl - 1];
            int rback = r - stoppers[rr - 1];

            ans += ppsumsum[N] - ppsumsum[rl - 2 + lback] - 
                   psum[rl - 1] * (N - (rl - 1 + lback) + 1);
            ans += ppsumsum[rr - 1 + rback] - ppsumsum[rr - 1] - psum[rr - 1] * rback;
        }

        cout << ans << endl;
    }
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
    // T = "change";
    while (T--) solve();

    return 0;
} 