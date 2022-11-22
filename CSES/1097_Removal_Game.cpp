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
#define INF 1000000000000000000ull
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

const int MAXN = 5010;
ll arr[MAXN];
ll dp[MAXN][MAXN];

ll solve(int lb, int ub)
{
    if (ub - lb <= 1) return max(arr[lb], arr[ub]);
    if (dp[lb][ub] != -INF) return dp[lb][ub];

    ll ans = -INF;
    ans = max(ans, min(solve(lb + 2, ub), solve(lb + 1, ub - 1)) + arr[lb]);
    ans = max(ans, min(solve(lb + 1, ub - 1), solve(lb, ub - 2)) + arr[ub]);
    return dp[lb][ub] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) dp[i][j] = -INF;

    cout << solve(1, N) << endl;
    return 0;
}