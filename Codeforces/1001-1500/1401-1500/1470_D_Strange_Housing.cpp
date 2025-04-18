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
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 300010;
int N, M;
vector<int> nbs[MAXN];
int color[MAXN];

void DFS(int a)
{
    color[a] = 2;
    for (int i = 0; i < nbs[a].size(); i++) 
        if (color[nbs[a][i]] == 2) color[a] = 1;
    
    for (int i = 0; i < nbs[a].size(); i++) if (!color[nbs[a][i]]) DFS(nbs[a][i]);
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1);

    bool has_ans = 1;
    vector<int> ans;
    for (int i = 1; i <= N; i++)
    {
        if (!color[i]) has_ans = 0;
        else if (color[i] == 2) ans.pb(i);
    }
    
    if (has_ans) 
    {
        cout << "YES" << endl;
        cout << ans.size() << endl;
        for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
        cout << endl;
    }
    else cout << "NO" << endl;

    for (int i = 1; i <= N; i++)
    {
        nbs[i].clear();
        color[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}