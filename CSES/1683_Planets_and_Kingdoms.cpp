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
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 500010;
int N, M;
vector<int> nbs[MAXN];
vector<int> nbs2[MAXN];
int k;
int kingdom[MAXN];
int vis[MAXN];
stack<int> kosa;

void DFS(int a)
{
    if (vis[a]) return;
    vis[a] = 1;
    for (int i = 0; i < nbs[a].size(); i++) DFS(nbs[a][i]);
    kosa.push(a);
}

void DFS2(int a, int v)
{
    if (vis[a]) return;
    vis[a] = 1;
    for (int i = 0; i < nbs2[a].size(); i++) DFS2(nbs2[a][i], v);
    kingdom[a] = v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a = read(), b = read();
        nbs[a].pb(b);
        nbs2[b].pb(a);
    }

    for (int i = 1; i <= N; i++) if (!vis[i]) DFS(i);
    reset(vis);
    
    int cnt = 0;
    while (!kosa.empty())
    {
        int v = kosa.top();
        // cout << v << " ";
        kosa.pop();
        if (vis[v]) continue;
        DFS2(v, ++cnt);
    }
    // cout << endl;

    cout << cnt << endl;
    for (int i = 1; i <= N; i++) cout << kingdom[i] << " ";
    cout << endl;
    return 0;
}