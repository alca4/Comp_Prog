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
struct Edge
{
    int n1, n2;
    ll v;

    bool operator<(Edge& e2)
    {
        return v < e2.v;
    }
} edges[MAXN];
int p[MAXN], sz[MAXN];

int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;
    if (sz[a] < sz[b])
    {
        sz[b] += sz[a];
        p[a] = b;
    }
    else
    {
        sz[a] += sz[b];
        p[b] = a;
    }
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;
    for (int i = 1; i <= M; i++) cin >> edges[i].n1 >> edges[i].n2 >> edges[i].v;
    sort(range(edges, 1, M));

    ll tot = 0;
    for (int i = 1; i <= M; i++) if (combine(edges[i].n1, edges[i].n2)) tot += edges[i].v;

    int pa = root(1);
    for (int i = 1; i <= N; i++) if (root(i) != pa)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << tot << endl;
    return 0;
}