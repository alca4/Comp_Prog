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

const int MAXN = 310;
const int D = 90000;
int arr[MAXN];
ll dp[MAXN][MAXN * MAXN * 2];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    dp[1][arr[2] + D] = 1;
    for (int i = 1; i <= N - 2; i++) for (int k = 0; k <= 180000; k++)
        if (dp[i][k]) 
        {
            dp[i + 1][arr[i + 2] + k] += dp[i][k];
            if (k - D != 0) dp[i + 1][arr[i + 2] - k + 2 * D] += dp[i][k];
            dp[i + 1][arr[i + 2] + k] %= MOD;
            dp[i + 1][arr[i + 2] - k + 2 * D] %= MOD;
        }
    
    int ans = 0;
    for (int i = 0; i <= 180000; i++) 
    {
        ans += dp[N - 1][i];
        ans %= MOD;
    }
    
    cout << ans << endl;
    return 0;
} 