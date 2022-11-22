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

const int MAXN = 1000010;
int N, M, Q;
int E;
int p[MAXN]; 
int w[MAXN];
vector<int> child[MAXN];
int up[MAXN][30];
int in[MAXN], out[MAXN];

int root(int a)
{
    return p[a] = (p[a] == a ? a : root(p[a]));
}

void combine(int a, int b, int d)
{
    a = root(a), b = root(b);
    if (a == b) return;
    E++;
    child[E].pb(a);
    child[E].pb(b);
    p[a] = p[b] = p[E] = E;
    up[a][0] = up[b][0] = up[E][0] = E;
    w[E] = d;
}

int T = 0;
void DFS(int a)
{
    in[a] = ++T;
    for (int i = 1; i < 30; i++) up[a][i] = up[up[a][i - 1]][i - 1];
    for (int i = 0; i < child[a].size(); i++) DFS(child[a][i]);
    out[a] = ++T;
}

int isAncestorOf(int a, int b)
{
    return in[a] < in[b] && out[b] < out[a];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;

    for (int i = 1; i <= N; i++) p[i] = i;
    E = N;

    for (int i = 1; i <= M; i++)
    {
        int v = M - i + 1;
        for (int j = 2 * v; j <= N; j += v) combine(j, j - v, i);
    }

    DFS(E);

    while (Q--)
    {
        int a, b;
        cin >> a >> b;

        int ans;
        if (isAncestorOf(a, b)) ans = a;
        else if (isAncestorOf(b, a)) ans = b;
        else 
        {
            for (int i = 29; i >= 0; i--)
                if (!isAncestorOf(up[a][i], b))
                    a = up[a][i];
            ans = up[a][0];
        }
        
        cout << w[ans] << endl;
    }
    return 0;
}