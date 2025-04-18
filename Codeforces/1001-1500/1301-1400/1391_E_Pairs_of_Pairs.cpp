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
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 500010;
int N, M;
vector<int> nbs[MAXN];
int D = 0;
vector<int> depth[MAXN];
int par[MAXN];
int vis[MAXN];

void DFS(int a, int p, int d)
{
    depth[d].pb(a);
    par[a] = p;
    vis[a] = 1;
    D = max(d, D);
    for (int i = 0; i < nbs[a].size(); i++) if (!vis[nbs[a][i]])
        DFS(nbs[a][i], a, d + 1);
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0, 1);

    if (D >= (N + 1) / 2)
    {
        cout << "PATH" << endl;
        vector<int> ans;
        int v = depth[D][0];
        for (int i = 1; i <= D; i++) 
        {
            ans.pb(v);
            v = par[v];
        }
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
        cout << endl;
    }
    else
    {
        cout << "PAIRING" << endl;
        vector<pii> pairs;
        for (int i = 1; i <= D; i++) for (int j = 0; j < depth[i].size() / 2; j++)
            pairs.pb({depth[i][j * 2], depth[i][j * 2 + 1]});
        cout << pairs.size() << endl;
        for (int i = 0; i < pairs.size(); i++) cout << pairs[i].FF << " " << pairs[i].SS << endl;
    }

    for (int i = 1; i <= N; i++) 
    {
        nbs[i].clear();
        depth[i].clear();
        par[i] = 0;
        vis[i] = 0;
        D = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}