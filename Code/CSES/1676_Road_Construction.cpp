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
    int n1, n2, v;

    bool operator<(Edge& e2)
    {
        return v < e2.v;
    }
};
vector<Edge> edges;
int p[MAXN], sz[MAXN];
multiset<int> rts, szs;

int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;
    if (sz[a] < sz[b]) swap(a, b);
    szs.erase(szs.find(sz[a]));
    szs.erase(szs.find(sz[b]));
    rts.erase(rts.find(b));
    sz[a] += sz[b];
    p[b] = a;
    szs.insert(sz[a]);
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) 
    {
        p[i] = i, sz[i] = 1;
        rts.insert(i);
        szs.insert(1);
    }

    for (int i = 0; i < M; i++) edges.pb({read(), read(), 0});

    for (int i = 0; i < M; i++) 
    {
        combine(edges[i].n1, edges[i].n2);
        cout << rts.size() << " " << *szs.rbegin() << endl;
    }
    return 0;
}