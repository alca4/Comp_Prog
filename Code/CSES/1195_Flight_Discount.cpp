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
#define INF 1000000000000000000ll
#define MOD 1000000007ll
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll read()
{
    ll a;
    cin >> a;
    return a;
}

const int MAXN = 500010;
vector<pll> nbs[MAXN * 2];
int vis[MAXN * 2];
ll dist[MAXN * 2];

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a;
        ll b, c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
        nbs[a + N].pb({b + N, c});
        nbs[a].pb({b + N, c / 2});
    }

    for (int i = 1; i <= 2 * N; i++) dist[i] = INF;
    for (int i = 1; i <= 2 * N; i++) vis[i] = 0;

    priority_queue<pll> pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty())
    {
        int n = pq.top().SS;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;
        if (vis[N] && vis[2 * N]) break;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            ll w = nbs[n][i].SS;

            if (dist[tar] > dist[n] + w)
            {
                dist[tar] = dist[n] + w;
                pq.push({-1 * dist[tar], tar});
            }
        }
    }

    cout << min(dist[N], dist[2 * N]) << endl;
    return 0;
}