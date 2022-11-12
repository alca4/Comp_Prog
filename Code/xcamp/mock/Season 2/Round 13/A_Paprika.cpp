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

const int MAXN = 200010;
int N;
vector<int> nbs[MAXN];
int sz[MAXN];
int ans = INF;
multiset<int> ancestors;
multiset<int> previous;

void findAns(int a, int b, int c)
{
    // cout << a << " " << b << " " << c << endl;
    ans = min(ans, max({a, b, c}) - min({a, b, c}));
}

void DFS(int a, int p)
{
    ++sz[a];

    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        DFS(nbs[a][i], a);
        sz[a] += sz[nbs[a][i]];
    }
}

void DFS2(int a, int p)
{
    if (ancestors.upper_bound((N - sz[a]) / 2 + sz[a]) != ancestors.end())
    {
        int a1 = *ancestors.upper_bound((N - sz[a]) / 2 + sz[a]);
        findAns(sz[a], a1 - sz[a], N - a1);
    }
    
    if (!ancestors.empty())
    {
        int a1 = *(--ancestors.upper_bound((N - sz[a]) / 2 + sz[a]));
        findAns(sz[a], a1 - sz[a], N - a1);
    }
    
    if (previous.upper_bound((N - sz[a]) / 2) != previous.end())
    {
        int a2 = *previous.upper_bound((N - sz[a]) / 2);
        findAns(sz[a], a2, N - a2 - sz[a]);
    }
    
    if (!previous.empty())
    {
        int a2 = *(--previous.upper_bound((N - sz[a]) / 2 + sz[a]));
        findAns(sz[a], a2, N - a2 - sz[a]);
    }
    
    ancestors.insert(sz[a]);

    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) 
    {
        DFS2(nbs[a][i], a);
        previous.insert(sz[nbs[a][i]]);
    }
    
    ancestors.erase(ancestors.find(sz[a]));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);
    DFS2(1, 0);
    cout << ans << endl;
    return 0;
} 