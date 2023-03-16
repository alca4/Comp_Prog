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
#define MOD 998244353ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 2010;
ll N, K;
vector<int> nbs[MAXN];
ll sz[MAXN];
ll dp[MAXN];
vector<int> ones;
vector<ll> szs;
ll cyc;
ll powN[MAXN], fac[MAXN];

ll add(ll a, ll b) {return (a + b) % MOD;}
ll mult(ll a, ll b) {return (a * b) % MOD;}

ll DFS(int a)
{
    sz[a] = 1;
    for (int i = 0; i < nbs[a].size(); i++) if (!sz[nbs[a][i]]) sz[a] += DFS(nbs[a][i]);
    return sz[a];
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        int n;
        cin >> n;
        if (n < 0) 
        {
            K++;
            ones.pb(i);
        }
        else 
        {
            nbs[n].pb(i);
            nbs[i].pb(n);
        }
    }

    szs.pb(0);
    for (int i = 0; i < K; i++) szs.pb(DFS(ones[i]));
    for (int i = 1; i <= N; i++) if (!sz[i]) 
    {
        DFS(i);
        cyc++;
    }

    powN[0] = fac[0] = 1;
    for (int i = 1; i <= K; i++) powN[i] = mult(powN[i - 1], N);
    for (int i = 1; i < K; i++) fac[i] = mult(fac[i - 1], i);

    dp[0] = 1;
    for (int i = 1; i <= K; i++) for (int j = K; j >= 1; j--) 
        dp[j] = add(dp[j], mult(dp[j - 1], szs[i]));
    
    ll ans = 0;
    for (int i = 1; i <= K; i++) ans = add(ans, mult(dp[i], mult(fac[i - 1], powN[K - i])));

    cout << add(mult(cyc, powN[K]), ans) << endl;
    return 0;
}