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

    queue<int> q;
    q.push(1);
    vis[1] = 1;
    while (!q.empty())
    {
        int a = q.front();
        q.pop();

        for (int i = 0; i < nbs[a].size(); i++)
        {
            if (!vis[nbs[a][i]])
            {
                vis[nbs[a][i]] = 1;
                q.push(nbs[a][i]);
                pv[nbs[a][i]] = a;
            }
        }
    }

    if (!vis[N])
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    stack<int> vals;
    int a = N;
    while (a != 1) 
    {
        vals.push(a);
        a = pv[a];
    }
    vals.push(1);
    
    cout << vals.size() << endl;
    while (!vals.empty())
    {
        cout << vals.top() << " ";
        vals.pop();
    }
    return 0;
}