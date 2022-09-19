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
#define INF 1000000000ull
// #define MOD 1000000007ull
 
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 100010;
int N, M;
vector<int> nbs[MAXN];
vector<int> tmp[MAXN];
ll dp[MAXN];
vector<ll> pref[MAXN];
vector<ll> suff[MAXN];
ll ans[MAXN];
 
void mult(ll& a, ll b) {a = (a * b) % M;}
 
// 0 is white, 1 is black
 
void Order(int a, int p)
{
    for (int i = 0; i < tmp[a].size(); i++) if (tmp[a][i] != p)
    {
        nbs[a].pb(tmp[a][i]);
        Order(tmp[a][i], a);
    }
}
 
void DFS(int a)
{
    dp[a] = 1;
    for (int i = 0; i < nbs[a].size(); i++) 
    {
        int nb = nbs[a][i];
        DFS(nb);
        mult(dp[a], 1 + dp[nb]);
    }
 
    ll p = 1;
    pref[a].resize(nbs[a].size());
    for (int i = 0; i < nbs[a].size(); i++) 
    {
        int nb = nbs[a][i];
        mult(p, 1 + dp[nb]);
        pref[a][i] = p;
    }
 
    ll s = 1;
    suff[a].resize(nbs[a].size());
    for (int i = nbs[a].size() - 1; i >= 0; i--) 
    {
        int nb = nbs[a][i];
        mult(s, 1 + dp[nb]);
        suff[a][i] = s;
    }
}
 
void Reroot(int a, int p)
{
    ans[a] = dp[a];
    
    for (int i = 0; i < nbs[a].size(); i++) 
    {
        int nb = nbs[a][i];

        dp[a] = 1;
        if (i > 0) mult(dp[a], pref[a][i - 1]);
        if (i < nbs[a].size() - 1) mult(dp[a], suff[a][i + 1]);
        if (p != 0) mult(dp[a], dp[p] + 1);
        mult(dp[nb], 1 + dp[a]);
 
        Reroot(nb, a);
 
        if (nbs[nb].size() > 0) dp[nb] = suff[nb][0];
        else dp[nb] = 1;
        mult(dp[a], 1 + dp[nb]);
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    cin >> N >> M;
    for (int i = 1; i < N; i++) 
    {
        int a, b;
        cin >> a >> b;
        tmp[a].pb(b);
        tmp[b].pb(a);
    }
 
    Order(1, 0);
    DFS(1);
    Reroot(1, 0);
 
    for (int i = 1; i <= N; i++) cout << ans[i] << endl;
    return 0;
}