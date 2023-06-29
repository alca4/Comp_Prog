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
#define INF 1000000000000000000ull
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
vector<pll> nbs[MAXN];
vector<pll> nbs2[MAXN];
struct Edge
{
    ll n1, n2, w;
} edges[MAXN];
ll dist[MAXN];
int rel[MAXN];
int vis[MAXN];
int N, M;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        ll a = read(), b = read(), c = read();
        nbs[a].pb({b, c});
        nbs2[b].pb({a, c});
        edges[i] = {a, b, c};
    }

    for (int i = 1; i <= N; i++) dist[i] = -INF;

    queue<int> q;
    q.push(N);
    vis[N] = 1;
    rel[N]++;
    while (!q.empty())
    {
        int n = q.front();
        // cout << n << endl;
        q.pop();

        for (int i = 0; i < nbs2[n].size(); i++)
        {
            int tar = nbs2[n][i].FF;
            if (!vis[tar]) 
            {
                rel[tar]++;
                vis[tar] = 1;
                q.push(tar);
            }
        }
    }

    reset(vis);

    q.push(1);
    vis[1] = 1;
    rel[1]++;
    while (!q.empty())
    {
        int n = q.front();
        // cout << n << endl;
        q.pop();

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            if (!vis[tar]) 
            {
                rel[tar]++;
                vis[tar] = 1;
                q.push(tar);
            }
        }
    }

    // for (int i = 1; i <= N; i++) if (rel[i] == 2) cout << i << endl;

    dist[1] = 0;
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= M; j++)
            dist[edges[j].n2] = max(dist[edges[j].n2], dist[edges[j].n1] + edges[j].w);

    for (int j = 1; j <= M; j++)
        if (rel[edges[j].n2] == 2 && dist[edges[j].n2] != INF && 
            dist[edges[j].n2] < dist[edges[j].n1] + edges[j].w)
        {
            cout << -1 << endl;
            return 0;
        }
    
    cout << dist[N] << endl;
    return 0;
}