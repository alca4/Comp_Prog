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

const int MAXN = 20;
int N, Q;
ll dp[1 << MAXN][MAXN];
ll ans[1 << MAXN];
int pref[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N;
    for (int i = 0; i < N; i++) 
    {
        bool done = 0;
        for (int j = 0; j < N; j++)
        {
            int n;
            cin >> n;
            n--;
            if (!done) pref[i] |= (1 << n);
            if (n == i) done = 1;
        }
    }

    ans[0] = 1;
    for (int i = 0; i < N; i++) 
        dp[1 << i][i] = 1;
    
    for (int i = 0; i < N; i++)
        for (int mask = (1 << i); mask < (1 << (i + 1)); mask++) 
        {
            for (int j = 0; j <= i; j++)
            {
                if (!(mask & (1 << j))) continue;
                for (int k = 0; k < i; k++)
                    if (!(mask & (1 << k)) && (pref[j] & (1 << k)))
                        dp[mask | (1 << k)][k] += dp[mask][j];
                if ((pref[j] & (1 << i))) ans[mask] += dp[mask][j];
            }
            for (int k = i + 1; k < N; k++)
                dp[mask | (1 << k)][k] += ans[mask];
        }
    
    cin >> Q;
    while (Q--)
    {
        int m1 = 0;
        int m2 = 0;
        for (int i = 0; i < N; i++)
        {
            char c;
            cin >> c;
            if (c == 'H') m1 |= (1 << i);
            else m2 |= (1 << i);
        }
        cout << ans[m1] * ans[m2] << endl;
    }
    return 0;
}