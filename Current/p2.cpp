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
#include <iostream>
#include <cmath>
#include <algorithm>
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

const int MAXN = 1010;
int N, M, K;
string s1, s2;
int dp[2][201][201][2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    cin >> s1 >> s2;
    s1 = '?' + s1;
    s2 = '!' + s2;

    dp[0][1][0][0] = 1;
    for (int i = 0; i <= N; i++) 
    {
		for (int j = 0; j <= M + 1; j++) for (int k = 0; k <= K; k++)
    	{
        	if (dp[0][j][k][0] == 0 && dp[0][j][k][1] == 0) continue;
        	if (s1[i] == s2[j])
        	{
            	dp[1][j + 1][k][1] += dp[0][j][k][1];
            	dp[1][j + 1][k + 1][1] += dp[0][j][k][0];
            	dp[1][j + 1][k + 1][1] += dp[0][j][k][1];

            	dp[1][j + 1][k][1] %= MOD;
            	dp[1][j + 1][k + 1][1] %= MOD;
        	}
        	dp[1][j][k][0] += dp[0][j][k][0];
        	dp[1][j][k][0] += dp[0][j][k][1];

        	dp[1][j][k][0] %= MOD;
    	}
        for (int j = 0; j <= M + 1; j++) for (int k = 0; k <= K; k++)
        {
            dp[0][j][k][0] = dp[1][j][k][0];
            dp[0][j][k][1] = dp[1][j][k][1];
            dp[1][j][k][0] = dp[1][j][k][1] = 0;
		}
    }

    cout << (dp[0][M + 1][K][0] + dp[0][M + 1][K][1]) % MOD << endl;
    return 0;
} 