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

const int MAXM = 1010;
int N, M;
ll dp[1024][2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;

    dp[0][0] = 1;
    for (int j = 0; j < M; j++) for (int i = 0; i < N; i++)
    {
        for (int mask = 0; mask < (1 << N); mask++)
        {
            dp[mask][1] = dp[mask ^ (1 << i)][0];
            if (i && !(mask & (1 << i)) && !(mask & (1 << i - 1)))
                dp[mask][1] += dp[mask ^ (1 << i - 1)][0];
            dp[mask][1] %= MOD;
        }
        for (int mask = 0; mask < (1 << N); mask++) dp[mask][0] = dp[mask][1];
    }
    cout << dp[0][0] << endl;
    return 0;
}