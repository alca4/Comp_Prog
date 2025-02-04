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
int N;
ll K;
pll arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = pii(0, 0);
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i].FF;
    for (int i = 1; i <= N; i++) cin >> arr[i].SS;

    sort(arr + 1, arr + 1 + N);

    int med = N / 2;
    ll ans = 0;
    for (int i = N; i >= 1; i--) {
        if (arr[i].SS == 1){
            if (i > med) ans = max(ans, arr[i].FF + K + arr[med].FF);
            else ans = max(ans, arr[i].FF + K + arr[med + 1].FF);
            break;
        }
    }

    ll lb = 0;
    ll ub = LINF;
    while (lb <= ub) {
        ll mid = (lb + ub) / 2;

        int num_greater = 0;
        deque<int> water;
        for (int i = 1; i <= N; i++) {
            if (arr[i].FF >= mid) num_greater++;
            if (arr[i].SS == 1) water.push_front(arr[i].FF);
        }

        ll TK = K;
        for (ll n : water) {
            if (TK >= mid - n) {
                if (mid - n > 0) num_greater++;
                TK -= max(0ll, mid - n);
            }
        }

        // cout << mid << " " << num_greater << " " << N - med + 1 << endl;

        if (num_greater < N - med + 1) ub = mid - 1;
        else {
            ans = max(ans, mid + arr[N].FF);
            lb = mid + 1;
        }
    }
    
    cout << ans << endl;
    reset_tc();
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