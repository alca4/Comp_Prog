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

const int MAXN = 5010;

int N;
int arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll ans = 0;
    for (int i = 1; i <= N; i++) ans += 1ll * (i - 1) * (N - i + 1);
    // cout << ans << endl;

    set<pii> order;
    for (int i = 1; i <= N; i++) order.insert(pii(arr[i], i));
    
    for (int i = 1; i <= N; i++) {
        int n = order.begin()->SS;
        order.erase(order.begin());

        vector<int> left;
        int l2 = n - 1;
        while (l2 >= 1 && arr[l2] > arr[n]) l2--;

        int l = l2;
        while (l >= 1 && arr[l] < arr[n]) l--;

        vector<int> right;
        int r = n + 1;
        while (r <= N && arr[r] > arr[n]) r++;

        ans -= 1ll * (r - n) * (l2 - l);
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