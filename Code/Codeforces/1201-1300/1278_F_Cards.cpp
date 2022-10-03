/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 998244353ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(ll a, ll b) {return (a + b) % MOD;}
ll mult(ll a, ll b) {return (a * b) % MOD;}

const int MAXN = 5010;
int N, M, K;
ll dp[MAXN][MAXN];

ll exp(ll a, ll b)
{
    ll ans = 1;
    while (b)
    {
        if (b % 2) ans = mult(ans, a);
        a = mult(a, a);
        b /= 2;
    }
    return ans;
}

ll modInv(int m)
{
    return exp(m, MOD - 2);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;

    dp[1][1] = N;
    for (int i = 1; i <= K; i++) for (int j = 1; j <= K; j++)
    {
        dp[i + 1][j + 1] = add(dp[i + 1][j + 1], mult(dp[i][j], N - j));
        dp[i + 1][j] = add(dp[i + 1][j], mult(dp[i][j], j));
    }

    ll ans = 0;
    for (int i = 1; i <= K; i++) ans = add(ans, mult(dp[K][i], modInv(exp(M, i))));

    cout << ans << endl;
    return 0;
}