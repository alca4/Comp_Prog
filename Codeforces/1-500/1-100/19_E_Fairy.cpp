/*
Idea: DFS
Build DFS tree, alternate depth with alternate colors
Denote edges good if connect opposite colors/bad if same
4 cases:
Remove bad back edge: if only bad edge, can remove
Remove good back edge: if there are no bad edges
Remove bad tree edge: that doesn't exist
Remove good tree edge: no good edges pass through that edge-use tree dp
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

const int MAXN = 10010;
int N, M;
vector<pii> nbs[MAXN];
int d[MAXN];
int bs[MAXN], gs[MAXN], be[MAXN], ge[MAXN];
int vis[MAXN];
vector<int> good, bad, ans;

void Fill(int a)
{
    vis[a] = 1;
    for (int i = 0; i < nbs[a].size(); i++) if (!vis[nbs[a][i].FF]) Fill(nbs[a][i].FF);
}

void DFS(int a, int p)
{
    vis[a] = 1;
    d[a] = d[p] + 1;
    for (int i = 0; i < nbs[a].size(); i++)
    {
        int nb = nbs[a][i].FF;
        if (!vis[nb]) 
        {
            DFS(nb, a);
            bs[a] += bs[nb];
            gs[a] += gs[nb];
            be[a] += be[nb];
            ge[a] += ge[nb];
        }
        else
        {
            if (nb != p && d[p] > d[nb])
            {
                if (d[nb] % 2 == d[a] % 2) 
                {
                    bs[a]++;
                    be[nb]++;
                    bad.pb(nbs[a][i].SS);
                }
                else 
                {
                    gs[a]++;
                    ge[nb]++;
                    good.pb(nbs[a][i].SS);
                }
            }
        }
    }
}

void DFS2(int a, int p)
{
    vis[a] = 1;
    bool can = 0;
    if (!be[a] && !(bs[0] - bs[a])) if (!bs[a] || !(gs[a] - ge[a])) can = 1;

    for (int i = 0; i < nbs[a].size(); i++)
    {
        int nb = nbs[a][i].FF;
        if (!vis[nb]) DFS2(nb, a);
        else if (nb == p && can) ans.pb(nbs[a][i].SS);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb({b, i});
        nbs[b].pb({a, i});
    }

    for (int i = 1; i <= N; i++) if (!vis[i])
    {
        nbs[0].pb({i, 0});
        Fill(i);
    }
    for (int i = 1; i <= N; i++) vis[i] = 0;
    for (int i = 1; i <= N; i++) if (!vis[i]) DFS(0, 0);
    for (int i = 1; i <= N; i++) vis[i] = 0;
    for (int i = 1; i <= N; i++) if (!vis[i]) DFS2(0, 0);

    if (bs[0] == 1) ans.pb(bad[0]);
    if (bs[0] == 0)
    {
        for (int i = 0; i < good.size(); i++) ans.pb(good[i]);
    }

    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}