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
#define INF 1000000000000000000ll
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 300010;
int N;
ll dp[MAXN][8];
ll t1[MAXN], t2[MAXN], t3[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> t1[i] >> t2[i] >> t3[i];

    for (int i = 0; i <= N; i++) for (int j = 0; j < 8; j++) dp[i][j] = INF;

    dp[0][0] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j < 8; j++)
        {
            dp[i][j | 1] = min(dp[i][j | 1], dp[i - 1][j] + t2[i] + t3[i]);
            dp[i][j | 2] = min(dp[i][j | 2], dp[i - 1][j] + t1[i] + t3[i]);
            dp[i][j | 4] = min(dp[i][j | 4], dp[i - 1][j] + t1[i] + t2[i]);
        }

    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        if (t1[i]) ans |= 1;
        if (t2[i]) ans |= 2;
        if (t3[i]) ans |= 4;
    }

    ll best = INF;
    for (int i = ans; i < 8; i++) if (ans | i == i) best = min(best, dp[N][i]);

    cout << best << endl;
    return 0;
}