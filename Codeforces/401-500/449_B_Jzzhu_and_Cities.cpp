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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 100010;
int N, M, K;
vector<pii> nbs[MAXN];
pii trains[MAXN];
int in[MAXN];

int dist[MAXN];
int vis[MAXN];
void Dijkstra(int src)
{
    for (int i = 1; i <= N; i++) dist[i] = INF, vis[i] = 0;
    dist[1] = 0;
    priority_queue<pii> pq;
    pq.push({0, 1});

    while (!pq.empty())
    {
        int n = pq.top().SS;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            int w = nbs[n][i].SS;
            if (dist[tar] > dist[n] + w) dist[tar] = dist[n] + w;
            if (!vis[tar]) pq.push({dist[tar] * -1, tar});
        }
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
        nbs[b].pb({a, c});
    }

    for (int i = 1; i <= K; i++)
    {
        int b, c;
        cin >> b >> c;
        trains[i] = {b, c};
        nbs[1].pb({b, c});
    }

    Dijkstra(1);

    for (int i = 1; i <= N; i++) for (int j = 0; j < nbs[i].size(); j++)
        if (dist[i] + nbs[i][j].SS == dist[nbs[i][j].FF]) in[nbs[i][j].FF]++;

    int ans = 0;
    for (int i = 1; i <= K; i++) 
    {
        if (dist[trains[i].FF] < trains[i].SS) ans++;
        else 
        {
            ans += (in[trains[i].FF] > 1);
            in[trains[i].FF]--;
        }
    }
    cout << ans << endl;
    return 0;
} 