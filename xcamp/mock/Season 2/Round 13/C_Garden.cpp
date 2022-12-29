/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 410;
int N, R, G, Y;
int arr[MAXN];
int dp[MAXN][MAXN][MAXN][3];
int nextv[MAXN][3];
int present[MAXN][3];
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        char c;
        cin >> c;
        if (c == 'R') 
        {
            arr[i] = 0;
            nextv[R][0] = i;
            R++;
        }
        if (c == 'G') 
        {
            arr[i] = 1;
            nextv[G][1] = i;
            G++;
        }
        if (c == 'Y') 
        {
            arr[i] = 2;
            nextv[Y][2] = i;
            Y++;
        }
    }

    present[0][0] = present[0][1] = present[0][2] = 0;
 
    for (int j = 0; j < 3; j++) 
    {
        for (int i = 1; i <= N; i++)
        {
            present[i][j] = present[i - 1][j];
            if (arr[i] == j) present[i][j]++;
        }
    }
 
    for (int i = 1; i <= N; i++) for (int r = 0; r <= R; r++) 
    for (int g = 0; g <= G; g++) for (int j = 0; j < 3; j++)
        dp[i][r][g][j] = INF;
 
    for (int i = 0; i <= N; i++) for (int r = 0; r <= R; r++) 
    for (int g = 0; g <= G; g++) for (int j = 0; j < 3; j++)
    {
        int y = i - r - g;
        if (y < 0 || y > Y) continue;
        
        if (dp[i][r][g][j] == INF) continue;
 
        if (r < R && j != 0)
        {
            int plus = nextv[r][0] + 
                       max(r - present[nextv[r][0]][0], 0) +
                       max(g - present[nextv[r][0]][1], 0) +
                       max(y - present[nextv[r][0]][2], 0) - i - 1;
            dp[i + 1][r + 1][g][0] = min(dp[i + 1][r + 1][g][0], dp[i][r][g][j] + plus);
        }
        
        if (g < G && j != 1)
        {
            int plus = nextv[g][1] + 
                       max(r - present[nextv[g][1]][0], 0) +
                       max(g - present[nextv[g][1]][1], 0) +
                       max(y - present[nextv[g][1]][2], 0) - i - 1;
            dp[i + 1][r][g + 1][1] = min(dp[i + 1][r][g + 1][1], dp[i][r][g][j] + plus);
        }
        
        if (y < Y && j != 2)
        {
            int plus = nextv[y][2] + 
                       max(r - present[nextv[y][2]][0], 0) +
                       max(g - present[nextv[y][2]][1], 0) +
                       max(y - present[nextv[y][2]][2], 0) - i - 1;
            dp[i + 1][r][g][2] = min(dp[i + 1][r][g][2], dp[i][r][g][j] + plus);
        }
    }
 
    if (dp[N][R][G][0] == INF && dp[N][R][G][1] == INF && dp[N][R][G][2] == INF) cout << -1 << endl;
    else cout << min({dp[N][R][G][0], dp[N][R][G][1], dp[N][R][G][2]}) << endl;
    return 0;
} 