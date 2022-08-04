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
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 510;
ll dp[MAXN][MAXN * MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll N;
    cin >> N;

    ll S = N * (N + 1) / 2;
    if (S % 2 == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    S /= 2;

    dp[0][0] = 1;
    for (int i = 0; i < N; i++) for (int j = 0; j <= S; j++)
    {
        dp[i + 1][j] += dp[i][j];
        dp[i + 1][j] %= MOD;
        if (j + i + 1 <= S) 
        {
            dp[i + 1][j + i + 1] += dp[i][j];
            dp[i + 1][j + i + 1] %= MOD;
        }
    }

    if (dp[N][S] % 2 == 1) cout << (dp[N][S] + MOD) / 2 << endl;
    else cout << dp[N][S] / 2 << endl;
    return 0;
}