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
ll INF = 1000000000000000000;
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
int N, M;
vector<pll> nbs[MAXN];
ll dist[MAXN];
int vis[MAXN];
ll numsp[MAXN];
int minsp[MAXN];
int maxsp[MAXN];

int main()
{
    srand(time(NULL));
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

    for (int i = 1; i <= N; i++) dist[i] = INF;
    dist[1] = 0;
    minsp[1] = maxsp[1] = 0;
    numsp[1] = 1;

    priority_queue<pll> pq;
    pq.push({0, 1});
    while (!pq.empty())
    {
        int n = pq.top().SS;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int j = 0; j < nbs[n].size(); j++)
        {
            int nb = nbs[n][j].FF;
            ll w = nbs[n][j].SS;

            if (dist[nb] > dist[n] + w)
            {
                minsp[nb] = minsp[n] + 1;
                maxsp[nb] = maxsp[n] + 1;
                numsp[nb] = numsp[n];
                dist[nb] = dist[n] + w;
                pq.push({dist[nb] * -1, nb});
            }
            else if (dist[nb] == dist[n] + w)
            {
                numsp[nb] += numsp[n];
                numsp[nb] %= MOD;
                minsp[nb] = min(minsp[nb], minsp[n] + 1);
                maxsp[nb] = max(maxsp[nb], maxsp[n] + 1);
            }
        }
    }

    cout << dist[N] << " " << numsp[N] << " " << minsp[N] << " " << maxsp[N] << endl;
    return 0;
} 