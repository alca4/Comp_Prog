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

const int MAXN = 3010;
int N, C;
vector<int> nbs[MAXN];
ll dp[MAXN][MAXN * 2];
ll ans[MAXN * 2];
int sz[MAXN];
vector<int> col[MAXN];
int v[MAXN];

ll tot = 0;

void DFS(int a, int p, int color)
{
    int c = col[color].size();
    dp[a][v[a] + MAXN] = 1;
    int lb = -c + 1;
    int ub = c;
    sz[a] = 1;
    for (int nb : nbs[a]) if (nb != p)
    {
        DFS(nb, a, color);
        for (int i = max(-c + 1, -sz[a]) + MAXN; i <= min(c, sz[a]) + MAXN; i++)
            for (int j = max(-c + 1, -sz[nb]) + MAXN; j <= min(c, sz[nb]) + MAXN; j++)
            {
                int id = i + j - MAXN;
                if (id < max(-c + 1, -sz[a] - sz[nb]) + MAXN || 
                    id > min(c, sz[a] + sz[nb]) + MAXN) continue;
                ans[id] += dp[a][i] * dp[nb][j];
                ans[id] %= MOD;
            }
        sz[a] += sz[nb];
        for (int i = max(-c + 1, -sz[a]) + MAXN; i <= min(c, sz[a]) + MAXN; i++) 
        {
            dp[a][i] += ans[i];
            dp[a][i] %= MOD;
            ans[i] = 0;
        }
    }
    for (int j = 1 + MAXN; j <= c + MAXN; j++)
    {
        tot += dp[a][j];
        tot %= MOD;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int n;
        cin >> n;
        col[n].pb(i);
        C = max(n, C);
        v[i] = -1;
    }
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= C; i++)
    {
        if (col[i].size() == 0) continue;
        for (int j = 0; j < col[i].size(); j++) v[col[i][j]] = 1;
        DFS(1, 0, i);

        int c = col[i].size();
        int lb = MAXN - c + 1;
        int ub = MAXN + c;

        for (int j = 1; j <= N; j++) 
        {
            for (int k = max(c - N + 1, -sz[j]) + MAXN; k <= min(c, sz[j]) + MAXN; k++) 
                dp[j][k] = 0;
        }
        for (int j = 0; j < col[i].size(); j++) v[col[i][j]] = -1;
    }
    cout << tot << endl;
    return 0;
}