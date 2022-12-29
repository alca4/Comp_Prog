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
ll MOD = 998244353;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
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

const int MAXN = 75;
int N, K, T;
ll dp[MAXN][MAXN * MAXN][MAXN];

ll fact[110];
ll factinv[110];

ll tab[110][110];

ll choose(int a, int b)
{
    if (b == 0) return 1;
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K >> T;
    fact[0] = factinv[0] = 1;
    for (int i = 1; i <= 100; i++) fact[i] = mult(fact[i - 1], i);
    for (int i = 1; i <= 100; i++) factinv[i] = divide(factinv[i - 1], i);

    for (int i = 1; i <= 100; i++) for (int j = 0; j <= i; j++) tab[i][j] = choose(i, j);
    
    for (int i = 0; i < K; i++) for (int j = 0; j <= (N + 1) * (N + 1); j++)
        for (int k = 0; k <= N; k++) dp[i][j][k] = 0;
    
    dp[0][0][N] = 1;

    for (int i = 0; i < K - 1; i++) for (int j = 0; j <= (N + 1) * (N + 1); j++)
        for (int k = N; k >= 0; k--)
    {
        if (dp[i][j][k] == 0) continue;
        for (int n = 0; n <= k; n++)
        {
            if (n == 0) 
            {
                // cout << i + 1 << " " << j << " " << k << endl;
                dp[i + 1][j][k] += dp[i][j][k];
                dp[i + 1][j][k] %= MOD;
            }
            else if (j + n * n <= (N + 1) * (N + 1))
            {
                // cout << i + 1 << " " << j + n * n << " " << k - n << endl;
                dp[i + 1][j + n * n][k - n] += dp[i][j][k] * tab[k][n];
                dp[i + 1][j + n * n][k - n] %= MOD;
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= N + 1; i++)
    {
        if (2 * T + N + 1 - i * i >= 0) 
            ans += dp[K - 1][2 * T + N + 1 - i * i][i - 1];
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
} 