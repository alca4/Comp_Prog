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

Tooting Bec
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
int N, M;
int a[MAXN], b[MAXN];
ll asum[MAXN], bsum[MAXN];

void reset_tc(int kmax) {
    for (int i = 1; i <= N; i++) a[i] = 0;
    for (int i = 1; i <= M; i++) b[i] = 0;
    for (int i = 1; i <= kmax; i++) asum[i] = bsum[i] = 0;
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= M; i++) cin >> b[i];

    sort(a + 1, a + 1 + N);
    sort(b + 1, b + 1 + M);
    
    int kmax = 1;
    while (max(0, 2 * kmax - M) <= min(kmax, N - kmax)) kmax++;
    vector<int> ans(kmax);
    kmax--;

    for (int i = 1; i <= kmax; i++) {
        asum[i] = asum[i - 1] + a[N - i + 1] - a[i];
        // cout << asum[i] << " ";
    }
    // cout << endl;
    for (int i = 1; i <= kmax; i++) {
        bsum[i] = bsum[i - 1] + b[M - i + 1] - b[i];
        // cout << bsum[i] << " ";
    }
    // cout << endl;

    cout << kmax << endl;
    for (int k = 1; k <= kmax; k++) {
        ll ans = 0;

        int lb = max(0, 2 * k - M);
        int ub = min(k, N - k);

        // cout << k << " " << lb << " " << ub << endl;

        while (lb <= ub) {
            int m1 = lb + (ub - lb) / 3;
            int m2 = ub - (ub - lb) / 3;

            ll a1 = asum[m1] + bsum[k - m1];
            ll a2 = asum[m2] + bsum[k - m2];

            ans = max(a1, a2);
            
            if (a1 < a2) lb = m1 + 1;
            else ub = m2 - 1;
        }
        cout << ans << " ";
    }
    cout << endl;

    reset_tc(kmax);
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