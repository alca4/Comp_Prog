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

const int MAXN = 200010;
int N, K, M;
ll C, D;

ll arr[MAXN];
int gt[MAXN];

void solve() {
    cin >> N >> K >> M >> C >> D;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll lb = 0, ub = LINF, ans = 0;
    while (lb <= ub) {
        ll mid = (lb + ub) / 2;
        // cout << mid << endl;

        for (int i = 1; i <= N; i++) arr[i] -= mid;

        for (int i = 1; i <= N; i++) {
            ll d = C + D * (min(i, M) - 1);
            arr[i] += d;
            if (arr[i] >= 0 && arr[i] - d < 0) {
                gt[max(i - M + 1, 1)]++;
                if (D && arr[i] < D * (min(i, M))) 
                    gt[min(max(i - M + 1, 1) + (int) (arr[i] / D) + 1, N + 1)]--;
                else gt[min(max(i - M + 1, 1) + min(i, M), N + 1)]--;
            }
            arr[i] -= d;
        }

        int ok = 0;
        int guarantee = 0;
        for (int i = 1; i <= N; i++) if (arr[i] >= 0) guarantee++;
        for (int i = 1; i <= N; i++) {
            gt[i] += gt[i - 1];
            // cout << gt[i] << " ";
            if (gt[i] >= K - guarantee) ok = 1;
        }
        // cout << endl;

        if (ok) {
            // cout << "ok" << endl;
            ans = mid;
            lb = mid + 1;
        }
        else ub = mid - 1;

        for (int i = 1; i <= N; i++) gt[i] = 0, arr[i] += mid;
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