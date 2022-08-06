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
vector<int> nbs[MAXN * 2];
vector<int> nbs2[MAXN * 2];
int vis[MAXN * 2];
int C;
int comp[MAXN * 2];
int fin[MAXN * 2];
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
    comp[a] = v;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    swap(N, M);
    for (int i = 1; i <= M; i++)
    {
        char a1, a2;
        int b1, b2;
        cin >> a1 >> b1 >> a2 >> b2;

        if (a1 == '+' && a2 == '+')
        {
            nbs[b1].pb(b2 + N);
            nbs[b2].pb(b1 + N);
            nbs2[b1 + N].pb(b2);
            nbs2[b2 + N].pb(b1);
        }
        if (a1 == '+' && a2 == '-')
        {
            nbs[b1].pb(b2);
            nbs[b2 + N].pb(b1 + N);
            nbs2[b1 + N].pb(b2 + N);
            nbs2[b2].pb(b1);
        }
        if (a1 == '-' && a2 == '+')
        {
            nbs[b1 + N].pb(b2 + N);
            nbs[b2].pb(b1);
            nbs2[b1].pb(b2);
            nbs2[b2 + N].pb(b1 + N);
        }
        if (a1 == '-' && a2 == '-')
        {
            nbs[b1 + N].pb(b2);
            nbs[b2 + N].pb(b1);
            nbs2[b1].pb(b2 + N);
            nbs2[b2].pb(b1 + N);
        }
    }

    for (int i = 1; i <= 2 * N; i++) if (!vis[i]) DFS(i);
    reset(vis);
    
    while (!kosa.empty())
    {
        int v = kosa.top();
        kosa.pop();
        int other = (v > N ? v - N : v + N);
        if (vis[other]) continue;
        // cout << v << " ";
        DFS2(v, ++C);
    }

    for (int i = 1; i <= N; i++) 
    {
        if (comp[i] == comp[i + N])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        fin[i] = comp[i] < comp[i + N];
    }

    for (int i = 1; i <= N; i++) 
    {
        if (fin[i]) cout << "- ";
        else cout << "+ ";
    }
    cout << endl;
    return 0;
}