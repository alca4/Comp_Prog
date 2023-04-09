/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
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
ll INF = INT_MAX;
ll LINF = LONG_MAX;
ll MOD = 1000000007;
// ll MOD = 998244353;

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
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
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

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 200010;
string str, tar;
int N;
int c[MAXN];
pii dp[MAXN][6];
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    tar = "bessie";

    cin >> str;
    N = (int) str.length();
    str = '#' + str;
    for (int i = 1; i <= N; i++) cin >> c[i];

    for (int i = 1; i <= N; i++) for (int j = 0; j < 6; j++) dp[i][j] = pii(0, -INF);

    dp[1][0] = pii(0, 0);
    for (int i = 1; i <= N; i++) for (int j = 0; j < 6; j++)
    {
        if (dp[i][j] == pii(0, -INF)) continue;
        if (str[i] == tar[j])
        {
            if (j == 5) maxeq(dp[i + 1][0], pii(dp[i][j].FF + 1, dp[i][j].SS));
            else maxeq(dp[i + 1][j + 1], dp[i][j]);
        }
        maxeq(dp[i + 1][0], dp[i][j]);
        maxeq(dp[i + 1][j], pii(dp[i][j].FF, dp[i][j].SS - c[i]));
    }

    pii ans = pii(0, -INF);
    for (int j = 0; j < 6; j++) maxeq(ans, dp[N + 1][j]);
    cout << ans.FF << endl;
    cout << ans.SS * -1 << endl;
    return 0;
} 