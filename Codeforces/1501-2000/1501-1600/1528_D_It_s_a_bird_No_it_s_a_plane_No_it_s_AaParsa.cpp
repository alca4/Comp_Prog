/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 610;
int N, M;
ll dist[MAXN];
vector<pll> nbs[MAXN];
int vis[MAXN];

void dijkstra(int a)
{
    for (int i = 0; i <= N; i++) dist[i] = INF, vis[i] = 0;
    int cur = a;

    for (int j = 0; j < nbs[cur].size(); j++) 
        dist[nbs[cur][j].FF] = nbs[cur][j].SS;

    while (cur != N)
    {
        int cur = N;
        for (int j = 0; j < N; j++) if (dist[j] < dist[cur] && !vis[j]) cur = j;

        if (cur == N) break;

        vis[cur] = 1;

        for (int j = 0; j < nbs[cur].size(); j++) 
        {
            int id = (nbs[cur][j].FF + dist[cur]) % N;
            if (!vis[id]) dist[id] = min(dist[id], dist[cur] + nbs[cur][j].SS);
        }

        if (!vis[(cur + 1) % N])
            dist[(cur + 1) % N] = min(dist[(cur + 1) % N], dist[cur] + 1);
    }

    dist[a] = 0;
    
    for (int j = 0; j < N; j++) cout << dist[j] << " ";
    cout << endl;
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
    }

    for (int i = 0; i < N; i++) dijkstra(i);

    return 0;
}