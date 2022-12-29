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

const int MAXN = 2510;
int N, M, K;
ll w[MAXN];
vector<int> nbs[MAXN];
int vis[MAXN];
int good[MAXN][MAXN];
vector<pll> best[MAXN];
queue<pii> q;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 2; i <= N; i++) cin >> w[i];
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++) vis[j] = 0;
        q.push({i, -1});
        vis[i] = 1;

        while (!q.empty())
        {
            int n = q.front().FF;
            int d = q.front().SS;
            q.pop();

            good[i][n] = 1;

            for (int j = 0; j < nbs[n].size(); j++)
                if (!vis[nbs[n][j]] && d < K) 
                {
                    q.push({nbs[n][j], d + 1});
                    vis[nbs[n][j]] = 1;
                }
        }
        good[i][i] = 0;
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        if (good[1][i] && good[i][j])
        {
            best[j].pb({w[i] + w[j], i});
            sort(best[j].rbegin(), best[j].rend());
            if (best[j].size() > 3) best[j].pop_back();
        }

    ll ans = 0;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        if (good[i][j])
            for (int a = 0; a < 3; a++) for (int b = 0; b < 3; b++)
            {
                best[i].resize(3);
                best[j].resize(3);
                if (i != best[j][b].SS && j != best[i][a].SS &&
                    best[j][b].SS != best[i][a].SS) 
                    ans = max(ans, best[i][a].FF + best[j][b].FF);
            }      
    
    cout << ans << endl;
    return 0;
} 