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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
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

const int MAXN = 300010;
int N;
int arr[MAXN];
int prefo[MAXN], suffz[MAXN], lastz[MAXN];
ll c1 = 1000000000000;
ll c2 = c1 + 1;

void solve() {
    string str;
    cin >> str;
    N = str.length();
    for (int i = 1; i <= N; i++) {
        arr[i] = str[i - 1] - '0';
    }

    for (int i = 1; i <= N; i++) {
        prefo[i] = prefo[i - 1];
        if (arr[i] == 1) prefo[i]++;
    }

    for (int i = N; i >= 1; i--) {
        suffz[i] = suffz[i + 1];
        if (arr[i] == 0) suffz[i]++;
    }

    int lz = 0;
    for (int i = 1; i <= N; i++) {
        lastz[i] = lz;
        if (arr[i] == 0) lz = i;
    }

    ll ans = LINF;
    for (int i = 1; i <= N; i++) {
        ll tans = (i - lastz[i] - 1) * c1 +
                  prefo[lastz[i]] * c2 +
                  suffz[i + 1] * c2;
        ans = min(ans, tans);
    }

    cout << ans << endl;

    for (int i = 1; i <= N; i++) arr[i] = prefo[i] = lastz[i] = suffz[i] = 0;
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