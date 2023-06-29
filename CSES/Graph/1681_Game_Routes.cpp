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

const int MAXN = 500010;
int N, M;
vector<int> nbs[MAXN];
ll dp[MAXN];
int vis[MAXN];

ll DFS(int a)
{
    if (a == N) return 1;
    if (vis[a]) return dp[a];
    vis[a] = 1;
    ll ans = 0;
    for (int i = 0; i < nbs[a].size(); i++)
    {
        ans += DFS(nbs[a][i]);
        ans %= MOD;
    }
    return dp[a] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) nbs[read()].pb(read());

    cout << DFS(1) << endl;
    return 0;
}