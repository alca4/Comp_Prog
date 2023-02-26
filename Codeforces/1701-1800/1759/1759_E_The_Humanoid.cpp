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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
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
ll arr[MAXN];

/*
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[i]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}
*/

ll dp[MAXN][3][2];

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        ll N, H;
        cin >> N >> H;
        for (int i = 1; i <= N; i++) cin >> arr[i];
        sort(arr + 1, arr + 1 + N);

        dp[1][2][1] = H;

        for (int i = 1; i <= N; i++)
            for (int g = 2; g >= 0; g--) for (int b = 1; b >= 0; b--)
        {
            if (dp[i][g][b])
            {
                if (arr[i] < dp[i][g][b]) maxeq(dp[i + 1][g][b], dp[i][g][b] + arr[i] / 2);
                if (g) maxeq(dp[i][g - 1][b], dp[i][g][b] * 2);
                if (b) maxeq(dp[i][g][b - 1], dp[i][g][b] * 3);
            }
        }

        int ans = 0;
         for (int i = 1; i <= N + 1; i++)
            for (int g = 2; g >= 0; g--) for (int b = 1; b >= 0; b--)
            {
                if (dp[i][g][b]) ans = max(ans, i - 1);
                dp[i][g][b] = 0;
            }
        cout << ans << endl;

        for (int i = 1; i <= N; i++) arr[i] = 0;
    }

    return 0;
} 