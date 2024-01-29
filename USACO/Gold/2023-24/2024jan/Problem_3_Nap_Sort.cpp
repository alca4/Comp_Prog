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
ll ans[MAXN];

ll check(int mid) {
    if (ans[mid]) return ans[mid];
    // cout << "answering " << mid << endl;
    ll max_untaken = 0;
    ll step_sum = 0;
    int step = mid;
    int last_taken = 0;
    for (int j = 1; j <= N; j++) {
        if (step && arr[j] >= step_sum + step) {
            step_sum += step;
            step--;
            last_taken = j;
        }
        else max_untaken = arr[j];
    }

    ll bessie_time = 1ll * mid * (mid + 1) / 2;

    // cout << mid << ": " << max_untaken << " " << bessie_time << endl;

    return ans[mid] = max(max_untaken, bessie_time);
}

void solve() {
    cin >> N;
    // cout << "N is: " << N << endl;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    sort(arr + 1, arr + 1 + N);
    arr[N + 1] = LINF;

    ll gans = LINF;
    int lb = 0;
    int ub = N;
    // cout << lb << " " << ub << endl;
    while (lb <= ub) {
        int m1 = lb + (ub - lb) / 3;
        int m2 = ub - (ub - lb) / 3;

        ll a1 = check(m1);
        ll a2 = check(m2);

        if (a1 >= a2) lb = m1 + 1;
        else ub = m2 - 1;
        gans = min({gans, a1, a2});
    }

    cout << gans << endl;

    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 0; i <= N; i++) ans[i] = 0;
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