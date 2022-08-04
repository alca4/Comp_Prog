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
int vis[MAXN];
int pv[MAXN];
int ans = 0;

void DFS(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++)
    {
        if (nbs[a][i] == p) continue;
        pv[nbs[a][i]] = a;
        if (vis[nbs[a][i]]) 
        {
            ans = nbs[a][i];
            return;
        }
        vis[nbs[a][i]] = 1;
        DFS(nbs[a][i], a);
        if (ans != 0) return;
    }
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
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) if (!vis[i])
    {
        vis[i] = 1;
        DFS(i, 0);
        if (ans != 0) break;
    }

    if (ans == 0)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    stack<int> vals;
    vals.push(ans);
    int tmp = pv[ans];
    while (tmp != ans)
    {
        vals.push(tmp);
        tmp = pv[tmp];
    }
    vals.push(ans);

    cout << vals.size() << endl;
    while (!vals.empty())
    {
        cout << vals.top() << " ";
        vals.pop();
    }
    cout << endl;

    return 0;
}