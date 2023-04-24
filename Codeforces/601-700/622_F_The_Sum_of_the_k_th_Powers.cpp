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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;

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
ll power(ll a, ll b)
{
    ll ans = 1;

    ll binexp[32];
    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (b > 0)
    {
        ans = mult(ans, binexp[__builtin_ctz(b & -b)]);
        b -= (b & -b);
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

const int MAXN = 1000010;
int N, K;
ll arr[MAXN];

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;

    for (int i = 1; i <= K + 1; i++) arr[i] = add(arr[i - 1], power(i, K));

    if (N <= K + 1) 
    {
        cout << arr[N] << endl;
        return 0;
    }

    ll ans = 0;
    ll up = 1;
    for (int i = 0; i <= K + 1; i++) multeq(up, N - i);
    ll bottom = divide(1, N);
    for (int i = 1; i <= K + 1; i++) diveq(bottom, MOD - i);
    for (int i = 0; i <= K + 1; i++)
    {
        addeq(ans, mult(arr[i], bottom));
        multeq(bottom, divide(mult(N - i, MOD - K - 1 + i), mult(i + 1, N - i - 1)));
    }

    cout << mult(ans, up) << endl;

    return 0;
} 