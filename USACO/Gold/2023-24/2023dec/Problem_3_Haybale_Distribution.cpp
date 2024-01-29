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

const int MAXN = 200010;
int N;
ll arr[MAXN];
int Q;
set<pii> nums;

ll get_ans(int m, int a, int b) {
    auto it = nums.lower_bound({m, 0});
    if (it == nums.end()) {
        return ((1ll * m * N) - arr[N]) * a;
    }

    int f = it->SS;
    // cout << f << endl;
    return (1ll * m * (f - 1) - arr[f - 1]) * a + (arr[N] - arr[f - 1] - 1ll * m * (N - f + 1)) * b;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }
    sort(arr + 1, arr + 1 + N);
    for (int i = 1; i <= N; i++) {
        nums.insert({arr[i], i});
        arr[i] += arr[i - 1];
    }

    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;

        int lb = 0, ub = 1000000;
        ll ans = LINF;
        while (lb <= ub) {
            int m1 = (ub - lb) / 3 + lb;
            int m2 = ub - (ub - lb) / 3;

            ll a1 = get_ans(m1, a, b);
            ll a2 = get_ans(m2, a, b);
            // cout << m1 << " " << m2 << ": " << a1 << " " << a2 << endl;
            if (a1 < a2) ub = m2 - 1;
            else lb = m1 + 1;
            ans = min({ans, a1, a2});
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