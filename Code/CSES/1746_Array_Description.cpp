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

const int MAXN = 100010;
int arr[MAXN];
ll dp[MAXN][110];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    if (arr[N] > 0) dp[N][arr[N]] = 1;
    else for (int j = 1; j <= M; j++) dp[N][j] = 1;
    for (int i = N - 1; i >= 1; i--)
    {
        if (arr[i] > 0) 
        {
            if (arr[i] > 1) dp[i][arr[i]] += dp[i + 1][arr[i] - 1];
            dp[i][arr[i]] += dp[i + 1][arr[i]];
            if (arr[i] < M) dp[i][arr[i]] += dp[i + 1][arr[i] + 1];
            dp[i][arr[i]] %= MOD;
        }
        else
        {
            for (int j = 1; j <= M; j++)
            {
                if (j > 1) dp[i][j] += dp[i + 1][j - 1];
                dp[i][j] += dp[i + 1][j];
                if (j < M) dp[i][j] += dp[i + 1][j + 1];
                dp[i][j] %= MOD;
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= 100; i++) ans = (ans + dp[1][i]) % MOD;
    cout << ans << endl;
    return 0;
}