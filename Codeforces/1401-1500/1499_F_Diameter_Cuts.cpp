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
#define MOD 998244353
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
int N, K;
vector<int> nbs[MAXN];
ll dp[MAXN][MAXN];
ll ans[MAXN];
int sz[MAXN];

void DFS(int a, int p)
{
    // cout << a << endl;
    dp[a][0] = 1;
    sz[a] = 1;
    for (int nb : nbs[a]) if (nb != p)
    {
        DFS(nb, a);
        for (int i = 0; i <= sz[a]; i++)
            for (int j = 0; j <= sz[nb]; j++)
            {
                if (i + j + 1 <= K) 
                {
                    ans[max(i, j + 1)] += dp[a][i] * dp[nb][j];
                    // cout << "can concatenate " << i << " " << j << " from " << a << " " << nb << endl;
                    ans[max(i, j + 1)] %= MOD;
                }
                if (i <= K && j <= K) 
                {
                    ans[i] += dp[a][i] * dp[nb][j];
                    ans[i] %= MOD;
                }
            }
        sz[a] += sz[nb];
        for (int i = 0; i <= sz[a]; i++) 
        {
            dp[a][i] = ans[i];
            dp[a][i] %= MOD;
            ans[i] = 0;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);

    ll tot = 0;
    for (int i = 0; i <= K; i++) 
    {
        tot += dp[1][i];
        tot %= MOD;
    }
    cout << tot << endl;
    return 0;
}