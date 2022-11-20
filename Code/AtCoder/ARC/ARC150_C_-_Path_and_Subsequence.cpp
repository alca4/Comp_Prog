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
#define INF 1000000000
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

const int MAXN = 200010;
int N, M, K;
vector<int> nbs[MAXN];
int a[MAXN];
int b[MAXN];
int dist[MAXN], vis[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= K; i++) cin >> b[i];

    for (int i = 1; i <= N; i++) dist[i] = INF;
    dist[1] = (a[1] == b[1]);

    priority_queue<pii> pq;
    pq.push({-dist[1], 1});
    while (!pq.empty())
    {
        int d = -pq.top().FF;
        int n = pq.top().SS;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int i = 0; i < nbs[n].size(); i++) if (!vis[nbs[n][i]])
        {
            if (a[nbs[n][i]] == b[d + 1]) 
                dist[nbs[n][i]] = min(dist[nbs[n][i]], dist[n] + 1);
            else dist[nbs[n][i]] = min(dist[nbs[n][i]], dist[n]);
            pq.push({-dist[nbs[n][i]], nbs[n][i]});
        }
    }

    if (dist[N] == K) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}