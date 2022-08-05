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
#define INF 10000000000000000ll
#define MOD 1000000007ll
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)
#define int ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll read()
{
    ll a;
    cin >> a;
    return a;
}

const int MAXN = 500010;
vector<pll> nbs[MAXN];
int vis[MAXN];
ll dist[MAXN];
vector<ll> best[MAXN];

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++) 
    {
        int a;
        ll b, c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
    }

    for (int i = 1; i <= N; i++) dist[i] = INF;
    for (int i = 1; i <= N; i++) vis[i] = 0;

    priority_queue<pll>pq;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty())
    {
        int v = pq.top().FF * -1;
        int n = pq.top().SS;
        best[n].pb(v);
        pq.pop();

        if (best[n].size() > K) continue;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            ll w = nbs[n][i].SS;

            if (best[tar].size() < K) pq.push({-1 * (v + w), tar});
        }
    }

    for (int i = 0; i < K; i++) cout << best[N][i] << " ";
    cout << endl;
    return 0;
}