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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 200010;
int N;

vector<ll> arr[2];
int hp[2];
ll ans[2];

void solve() {
    cin >> N;
    // cout << "=====" << endl;
    arr[0].pb(0), arr[1].pb(0);
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        if (n > 0) hp[i % 2] = 1;
        arr[i % 2].pb(n);
    }

    for (int j = 0; j < 2; j++) {
        if (hp[j]) {
            ans[j] = 0;
            for (int i = 1; i < arr[j].size(); i++) {
                if (arr[j][i] > 0) ans[j] += arr[j][i];
            }
        }
        else {
            ans[j] = -LINF;
            for (int i = 1; i < arr[j].size(); i++) ans[j] = max(ans[j], arr[j][i]);
        }
    }

    cout << max(ans[0], ans[1]) << endl;

    for (int j = 0; j < 2; j++) {
        arr[j].clear();
        ans[j] = 0;
        hp[j] = 0;
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 