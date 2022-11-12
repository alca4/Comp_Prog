/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
Yes I understand shortest path
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ll
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

const int MAXN = 1510, MAXM = 5010;
int N, M;
vector<pll> nbs[MAXN];
vector<pll> nbs2[MAXN];
ll dist[MAXN];
int vis[MAXN];
ll sp[MAXN];
ll dp[MAXN], ans[MAXM];
int E;
struct Edge
{
    int n1, n2, w;
} edgelist[MAXM];

priority_queue<pll> pq;
multiset<pll> topsort;

void solve(int a)
{
    // cout << a << " =====" << endl;
    for (int i = 1; i <= N; i++) dist[i] = INF, vis[i] = 0, dp[i] = 0, sp[i] = 0;

    pq.push({0, a});
    dist[a] = 0;
    while (!pq.empty())
    {
        int n = pq.top().SS;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            ll w = nbs[n][i].SS;

            if (dist[n] + w < dist[tar])
            {
                dist[tar] = dist[n] + w;
                if (!vis[tar]) pq.push({dist[tar] * -1, tar});
            }
        }
    }

    for (int i = 1; i <= N; i++) topsort.insert({dist[i], i});

    sp[a] = 1;
    for (int i = 1; i <= N; i++)
    {
        int n = topsort.begin()->SS;
        topsort.erase(topsort.begin());
        for (int j = 0; j < nbs[n].size(); j++) 
        {
            if (dist[n] + nbs[n][j].SS > dist[nbs[n][j].FF]) continue;
            sp[nbs[n][j].FF] += sp[n];
            sp[nbs[n][j].FF] %= MOD;
        }
    }

    for (int i = 1; i <= N; i++) topsort.insert({dist[i] * -1, i});

    for (int i = 1; i <= N; i++)
    {
        int n = topsort.begin()->SS;
        topsort.erase(topsort.begin());
        dp[n]++;
        dp[n] %= MOD;
        for (int j = 0; j < nbs2[n].size(); j++)
        {
            int tar = nbs2[n][j].FF;
            ll v = nbs2[n][j].SS;

            if (dist[tar] + v == dist[n]) 
            {
                dp[tar] += dp[n];
                dp[tar] %= MOD;
            }
        }
    }

    // for (int i = 1; i <= N; i++) cout << dp[i] << " ";
    // cout << endl;

    for (int i = 1; i <= M; i++)
    {
        int n1 = edgelist[i].n1;
        int n2 = edgelist[i].n2;
        int w = edgelist[i].w;

        if (dist[n1] + w == dist[n2])
            ans[i] += sp[n1] * dp[n2];
        ans[i] %= MOD;
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
        int a, b, c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
        nbs2[b].pb({a, c});
        edgelist[++E] = {a, b, c};
    }

    for (int i = 1; i <= N; i++) solve(i);

    for (int i = 1; i <= M; i++) cout << ans[i] << endl;
    return 0;
}