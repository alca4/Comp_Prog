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
#define INF 1000000000ll
#define MOD 1000000000000000000

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
int N;
int v[MAXN];
vector<int> nbs[MAXN];
vector<int> mults[MAXN];
int vis[MAXN];
ll ans[MAXN];

void DFS(int a, int p)
{
    for (int i = 1; i <= sqrt(v[a]); i++) 
    {
        if (v[a] % i == 0)
        {
            mults[i].pb(a);
            if (i != sqrt(v[a])) mults[v[a] / i].pb(a);
            // cout << v[a] << " divides " << i << " and " << v[a] / i << endl;
        }
    }

    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) DFS(nbs[a][i], a);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> v[i];
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);

    for (int i = 1; i <= N; i++) vis[i] = 1;

    for (int i = 1; i <= 200000; i++)
    {
        for (int j = 0; j < mults[i].size(); j++) vis[mults[i][j]] = 0;
        for (int j = 0; j < mults[i].size(); j++) if (!vis[mults[i][j]])
        {
            vis[mults[i][j]] = 1;
            ll sz = 1;
            queue<int> bfs;
            bfs.push(mults[i][j]);
            while (!bfs.empty())
            {
                int n = bfs.front();
                bfs.pop();

                for (int k = 0; k < nbs[n].size(); k++)
                {
                    if (!vis[nbs[n][k]])
                    {
                        vis[nbs[n][k]] = 1;
                        sz++;
                        bfs.push(nbs[n][k]);
                    }
                }
            }
            ans[i] += sz * (sz - 1) / 2 + sz;
        }
    }

    for (int i = 200000; i >= 1; i--) 
        for (int j = 2; i * j <= 200000; j++) 
            ans[i] -= ans[i * j];

    for (int i = 1; i <= 200000; i++) if (ans[i]) cout << i << " " << ans[i] << endl;
    
    return 0;
} 