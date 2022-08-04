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
int p[MAXN], sz[MAXN];
pii edges[MAXN];

int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

void combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return;
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
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N = read(), M = read();
    for (int i = 1; i <= M; i++) edges[i] = {read(), read()};
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;

    for (int i = 1; i <= M; i++) 
    {
        combine(edges[i].FF, edges[i].SS);
    }

    set<int> roots;
    for (int i = 1; i <= N; i++) roots.insert(root(i));

    int tot = roots.size() - 1;
    cout << tot << endl;
    for (int i = 1; i <= tot; i++)
    {
        cout << *roots.begin() << " " << *roots.rbegin() << endl;
        roots.erase(roots.begin());
    }
    return 0;
}