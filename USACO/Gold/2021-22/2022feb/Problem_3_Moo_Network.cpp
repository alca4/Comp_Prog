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

const int MAXN = 100010;
int N;

int E = 0;
struct Edge
{
    ll n1, n2, w;

    bool operator<(const Edge& other)
    {
        return w < other.w;
    }
} edges[MAXN * 20];
map<int, vector<pll>> cows;
pll last[11];

int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = p[a] == a ? a : root(p[a]);}
int combine(Edge e)
{
    int a = root(e.n1);
    int b = root(e.n2);

    if (a == b) return 0;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int x, y;
        cin >> x >> y;
        cows[x].pb({y, i});
    }

    for (auto n : cows)
    {
        for (int k = 0; k < n.SS.size(); k++)
        {
            int y = n.SS[k].FF;
            int i = n.SS[k].SS;
            for (int j = 0; j <= 10; j++) 
            {
                if (last[j] == pll(0, 0)) continue;

                edges[++E] = {last[j].SS, i, (j - y) * (j - y) + 
                            (n.FF - last[j].FF) * (n.FF - last[j].FF)};
            }
            last[y] = {n.FF, i};
        }
    }

    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;

    sort(edges + 1, edges + E + 1);

    ll tot = 0;
    for (int i = 1; i <= E; i++) if (combine(edges[i])) tot += edges[i].w;

    cout << tot << endl;
    return 0;
}