/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
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

const int MAXN = 1010;
int N;
int grid[MAXN][MAXN];
ll dp[MAXN][MAXN];

int DFS(int i, int j)
{
    if (dp[i][j] != -1) return dp[i][j];
    if (i == N && j == N) return 1;
    int ans = 0;
    if (i + 1 <= N && !grid[i + 1][j]) ans += DFS(i + 1, j);
    if (j + 1 <= N && !grid[i][j + 1]) ans += DFS(i, j + 1);
    return dp[i][j] = ans % MOD;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
    {
        char c;
        cin >> c;
        if (c == '*') grid[i][j] = 1;
        dp[i][j] = -1;
    }

    cout << (grid[1][1] == 1 ? 0 : DFS(1, 1) % MOD) << endl;
    return 0;
}