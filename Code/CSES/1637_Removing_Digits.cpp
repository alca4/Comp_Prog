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

const int MAXN = 1000010;
int N;
int dp[MAXN];

int cnt = 0;
int solve(int a)
{
    if (a == 0) return 0;
    if (dp[a] != 0) return dp[a];
    int ans = INF;
    int dig = a;
    while (dig > 0) 
    {
        if (dig % 10 == 0) 
        {
            dig /= 10;
            continue;
        }
        ans = min(ans, solve(a - (dig % 10)) + 1);
        dig /= 10;
    }
    // cout << a << " has ans " << ans << endl;
    return dp[a] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    cout << solve(N) << endl;
    return 0;
}