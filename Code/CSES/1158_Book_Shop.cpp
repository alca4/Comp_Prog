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
ll p[MAXN];
ll v[MAXN];
ll dp[2][100010];
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int N, X;
    cin >> N >> X;
    for (int i = 1; i <= N; i++) cin >> p[i];
    for (int i = 1; i <= N; i++) cin >> v[i];
 
    for (int j = 0; j <= 100000; j++) dp[0][j] = dp[1][j] = -1;
 
    dp[0][0] = 0;
    for (int i = 0; i < N; i++) for (int j = 0; j <= 100000; j++)
    {
        if (dp[i % 2][j] >= 0)
        {
            if (j + p[i + 1] <= 100000)
                dp[(i + 1) % 2][j + p[i + 1]] = max(dp[(i + 1) % 2][j + p[i + 1]], 
                                                    dp[i % 2][j] + v[i + 1]);
            dp[(i + 1) % 2][j] = max(dp[(i + 1) % 2][j], dp[i % 2][j]);
        }
    }
    
    ll ans = -1;
    for (int j = 0; j <= X; j++) ans = max(ans, dp[N % 2][j]);
    cout << ans << endl;
    return 0;
}