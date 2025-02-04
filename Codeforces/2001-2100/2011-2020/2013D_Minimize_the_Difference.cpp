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
vector<pll> guys;

void insert(ll a, ll b) {
    ll sum = guys.back().FF;
    ll cnt = guys.back().SS;
    guys.pop_back();

    if (a / b <= sum / cnt) {
        sum = sum + a;
        cnt += b;

        ll extra = sum % cnt;
        if (extra) {
            if (guys.size()) insert(sum / cnt * (cnt - extra), cnt - extra);
            else guys.pb(pll(sum / cnt * (cnt - extra), cnt - extra));


            if (guys.size()) insert((sum / cnt + 1) * extra, extra);
            else guys.pb(pll((sum / cnt + 1) * extra, extra));
        }
        else {
            if (guys.size()) insert(sum, cnt);
            else guys.pb(pll(sum, cnt));
        }
    }
    else {
        guys.pb(pll(sum, cnt));
        guys.pb(pll(a, b));
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    
    guys.pb(pll(arr[1], 1));

    for (int i = 2; i <= N; i++) {
        if (guys.size()) insert(arr[i], 1);
    }

    cout << guys.back().FF / guys.back().SS - guys[0].FF / guys[0].SS << endl;

    for (int i = 1; i <= N; i++) arr[i] = 0;
    guys.clear();
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