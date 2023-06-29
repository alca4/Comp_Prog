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
int dp[MAXN][MAXN];

int solve(int a, int b)
{
    if (a < b) swap(a, b);
    if (dp[a][b] != 0) return dp[a][b];
    if (a == b) return 0;

    int ans = INF;
    for (int i = 1; i < b; i++)
        ans = min(ans, solve(a, i) + solve(a, b - i) + 1);
    
    for (int i = 1; i < a; i++)
        ans = min(ans, solve(i, b) + solve(a - i, b) + 1);
    
    return dp[a][b] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a = read(), b = read();

    cout << solve(a, b) << endl;
    return 0;
}