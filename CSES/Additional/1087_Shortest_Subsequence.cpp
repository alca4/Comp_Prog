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

const int MAXN = 1000010;
int N;
string str;
int nv[MAXN][4];
set<string> setty;

void solve() {
    cin >> str;
    N = str.length();
    str = ' ' + str;
    str += "AGCT";

    for (int i = 0; i < 4; i++) nv[N][i] = N + i + 1;

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < 4; j++) nv[i][j] = nv[i + 1][j];
        if (str[i + 1] == 'A') nv[i][0] = i + 1;
        if (str[i + 1] == 'G') nv[i][1] = i + 1;
        if (str[i + 1] == 'C') nv[i][2] = i + 1;
        if (str[i + 1] == 'T') nv[i][3] = i + 1;
        // for (int j = 0; j < 4; j++) cout << nv[i][j] << " ";
        // cout << endl;
    }

    int p = 0;
    while (p <= N) {
        int nextv = max({nv[p][0], nv[p][1], nv[p][2], nv[p][3]});
        // cout << nextv << " ";
        cout << str[nextv];
        p = nextv;
    }
    cout << endl;
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