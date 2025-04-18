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
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll subtract(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
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

const int MAXN = 200010;
vector<vector<int>> vec;
vector<pii> nbs[MAXN];
int vis[MAXN];
int dist[MAXN];
int N, M, H;

ll DFS(int a)
{
    vis[a] = 1;

    ll ans = 1;

    for (int i = 0; i < nbs[a].size(); i++) 
    {
        if (vis[nbs[a][i].FF])
        {
            if (dist[nbs[a][i].FF] != (dist[a] + nbs[a][i].SS) % H) return 0;
        }
        else
        {
            dist[nbs[a][i].FF] = (dist[a] + nbs[a][i].SS) % H;
            ans *= DFS(nbs[a][i].FF);
        }
    }

    return ans;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N >> M >> H;

        vec.resize(N);
        for (int i = 0; i < N; i++) 
        {
            vec[i].resize(M);
            for (int j = 0; j < M; j++) cin >> vec[i][j];
        }

        for (int i = 0; i < N; i++)
        {
            int lnz = -1;
            for (int j = 0; j < M; j++) 
            {
                if (vec[i][j] >= 0)
                {
                    if (lnz >= 0) 
                    {
                        nbs[lnz].pb({j, (H + vec[i][j] - vec[i][lnz]) % H});
                        nbs[j].pb({lnz, (H + vec[i][lnz] - vec[i][j]) % H});
                    }
                    lnz = j;
                }
            }
        }

        ll ans = 1;
        ll components = 0;

        for (int i = 0; i < M; i++) if (!vis[i]) 
        {
            ans *= DFS(i);
            components++;
        }

        for (int i = 0; i < N; i++) 
        {
            bool good = 0;
            for (int j = 0; j < M; j++) if (vec[i][j] != -1) good = 1;
            if (!good) components++;
        }

        cout << ans * power(H, components - 1) << endl;

        vec.clear();
        for (int i = 0; i < M; i++) 
        {
            nbs[i].clear();
            dist[i] = vis[i] = 0;
        }
    }

    return 0;
} 