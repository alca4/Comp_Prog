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
vector<int> nbs[MAXN][2];
int vis[MAXN][2];

void DFS(int a, int t)
{
    if (vis[a][t]) return;
    vis[a][t] = 1;
    for (int i = 0; i < nbs[a][t].size(); i++) DFS(nbs[a][t][i], t);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) 
    {
        int a = read(), b = read();
        nbs[a][0].pb(b);
        nbs[b][1].pb(a);
    }

    DFS(1, 0);
    DFS(1, 1);
    for (int i = 1; i <= N; i++)
    {
        if (!vis[i][0])
        {
            cout << "NO" << endl;
            cout << "1 " << i << endl;
            return 0;
        }
        if (!vis[i][1])
        {
            cout << "NO" << endl;
            cout << i << " 1" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;

    return 0;
}