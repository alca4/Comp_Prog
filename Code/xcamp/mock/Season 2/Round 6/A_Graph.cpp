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
#define INF 1000000000
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 100010;
int N, M, Q;
vector<pii> nbs[MAXN];
int cont[MAXN];
int dist[MAXN];
pii edges[2 * MAXN];
set<int> good;

int ans = 0;

void chain(int a)
{
    for (int i = 0; i < nbs[a].size(); i++)
    {
        if (good.find(nbs[a][i].SS) == good.end()) continue;
        int nb = nbs[a][i].FF;
        if (dist[nb] != dist[a] + 1) continue;
        if (!cont[nb]) continue;

        good.erase(nbs[a][i].SS);
        cont[nb]--;
        // cout << "decreased clout of " << nb << endl;
        if (!cont[nb]) 
        {
            ans++;
            chain(nb);
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb({b, i});
        nbs[b].pb({a, i});
        edges[i] = pii(a, b);
    }

    for (int i = 1; i <= N; i++) dist[i] = INF;

    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty())
    {
        int n = q.front();
        q.pop();

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int nb = nbs[n][i].FF;
            if (dist[nb] == INF) q.push(nb);
            dist[nb] = min(dist[nb], dist[n] + 1);
            if (dist[nb] == dist[n] + 1) 
            {
                cont[nb]++;
                good.insert(nbs[n][i].SS);
            }
        }
    }

    while (Q--)
    {
        int n;
        cin >> n;

        int a = edges[n].FF;
        int b = edges[n].SS;
        
        if (dist[b] < dist[a]) swap(a, b); // a goes to b

        if (dist[a] + 1 != dist[b] || good.find(n) == good.end()) 
        {
            cout << ans << endl;
            continue;
        }
        good.erase(n);
        cont[b]--;
        // cout << "decreased clout of " << b << endl;
        if (!cont[b]) 
        {
            ans++;
            chain(b);
        }
        cout << ans << endl;
    }
    
    return 0;
}