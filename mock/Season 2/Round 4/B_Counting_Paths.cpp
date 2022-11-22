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

void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}
void add(ll& a, ll b) {a = (a + b) % MOD;}
void mult(ll& a, ll b) {a = (a * b) % MOD;}

int N, M, K;
int arr[310][310];
ll dp[310][2][2010];
int ids[1000010];
int vals[2010];

ll ans = 0;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> arr[i][j];

    int base = K / arr[N][M];
    for (int i = 1; i <= base + 1; i++) ids[base / i] = 1;
    int cnt = 0;
    for (int i = 0; i <= base; i++) 
    {
        if (ids[i])
        {
            vals[cnt] = i;
            ids[i] = cnt;
            cnt++;
        }
    }

    dp[N][1][ids[base]] = 1;
    for (int j = M; j >= 1; j--) 
    {
        for (int i = N; i >= 1; i--)
        {
            for (int k = 0; k < cnt; k++)
            {
                if (i > 1) 
                {
                    add(dp[i - 1][1][ids[vals[k] / arr[i - 1][j]]], dp[i][1][k]);
                    
                }
                if (j > 1) 
                {
                    add(dp[i][0][ids[vals[k] / arr[i][j - 1]]], dp[i][1][k]);
                }
            }
        }
        if (j == 1) add(ans, dp[1][1][0]);
        for (int i = N; i >= 1; i--)
        {
            for (int k = 0; k < cnt; k++)
            {
                dp[i][1][k] = dp[i][0][k];
                dp[i][0][k] = 0;
            }
        }
    }

    if (K % arr[N][M] == 0) dp[N][1][ids[base]] = 1;
    for (int j = M; j >= 1; j--)
    {
        for (int i = N; i >= 1; i--) 
        {
            for (int k = 0; k < cnt; k++)
            {
                if (i > 1) 
                {
                    if (vals[k] % arr[i - 1][j] == 0)
                        add(dp[i - 1][1][ids[vals[k] / arr[i - 1][j]]], dp[i][1][k]);
                }
                if (j > 1) 
                {
                    if (vals[k] % arr[i][j - 1] == 0)
                        add(dp[i][0][ids[vals[k] / arr[i][j - 1]]], dp[i][1][k]);
                }
            }
        }
        if (j == 1) add(ans, dp[1][1][1]);
        for (int i = N; i >= 1; i--)
        {
            for (int k = 0; k < cnt; k++)
            {
                dp[i][1][k] = dp[i][0][k];
                dp[i][0][k] = 0;
            }
        }
    }

    cout << ans << endl;
    return 0;
}