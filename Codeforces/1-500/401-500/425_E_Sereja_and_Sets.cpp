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
ll MOD = 1000000007;

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

const int MAXN = 510;
int N, K;
ll dp[MAXN][MAXN][2];
ll pow2[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    dp[0][0][0] = 1;
    pow2[0] = 1;
    for (int i = 1; i <= N; i++) pow2[i] = (pow2[i - 1] * 2) % MOD;

    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j <= i; j++) for (int k = 0; k <= i; k++)
        {
            dp[j + 1][i + 1][1] += dp[j][k][0] * (pow2[i + 1] + MOD - pow2[k]);
            dp[j + 1][i + 1][1] %= MOD;
            dp[j][k][1] += dp[j][k][0] * pow2[k];
            dp[j][k][1] %= MOD;
        }
        for (int j = 0; j <= i + 1; j++) for (int k = 0; k <= i + 1; k++)
        {
            dp[j][k][0] = dp[j][k][1];
            dp[j][k][1] = 0;
        }
    }

    ll ans = 0;
    for (int i = 0; i <= N; i++) ans += dp[K][i][0];
    cout << ans % MOD << endl;
    return 0;
} 