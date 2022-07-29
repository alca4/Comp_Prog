/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010, MAXM = 200010, MAXNM = 300010;
int N, M, Q;

int p[MAXNM], w[MAXNM];
vector<int> child[MAXNM];
int E;
struct Edge
{
    int n1, n2, v;
} edges[MAXM];
int lift[MAXNM][30];
int T;
int in[MAXNM], out[MAXNM];
int f[MAXN];

struct ST
{
    int seg[4 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        int ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans = max(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = max(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        return ans;
    }

    void clear(int cid, int ss, int se)
    {
        if (ss == se) return;
        seg[cid] = 0;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST seg;

int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

void combine(int i)
{
    int a = root(edges[i].n1);
    int b = root(edges[i].n2);

    if (a == b) return;
    w[++E] = i;
    p[a] = p[b] = p[E] = E;
    child[E].pb(a);
    child[E].pb(b);
    lift[a][0] = E;
    lift[b][0] = E;
}

void DFS(int a)
{
    // cout << a << endl;
    in[a] = ++T;
    for (int i = 0; i < 25; i++)
        lift[a][i + 1] = lift[lift[a][i]][i];
    for (int i = 0; i < child[a].size(); i++)
        DFS(child[a][i]);
    out[a] = ++T;
}

int isAncestorOf(int a, int b)
{
    return in[a] < in[b] && out[b] < out[a];
}

int lca(int a, int b)
{
    if (isAncestorOf(a, b)) return a;
    if (isAncestorOf(b, a)) return b;

    for (int i = 25; i >= 0; i--)
        if (!isAncestorOf(lift[a][i], b))
            a = lift[a][i];

    return lift[a][0];
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> M >> Q;
    E = N;

    for (int i = 1; i <= N; i++) p[i] = i;
    
    for (int i = 1; i <= M; i++) 
    {
        edges[i] = {read(), read(), i};
        combine(i);
    }

    lift[E][0] = E;
    DFS(E);

    for (int i = 2; i <= N; i++) f[i] = w[lca(i, i - 1)];
    for (int i = 2; i <= N; i++) seg.update(i, f[i], 1, 1, N);
    
    // for (int i = 1; i <= 2 * N - 1; i++) cout << seg.seg[i] << " ";
    // cout << endl;

    while (Q--)
    {
        int a = read();
        int b = read();

        if (a == b) cout << "0 ";
        else cout << seg.query(a + 1, b, 1, 1, N) << " ";
    }
    cout << endl;

    seg.clear(1, 1, N);
    for (int i = 1; i <= N + M; i++) 
    {
        p[i] = w[i] = in[i] = out[i] = 0;
        child[i].clear();
        for (int j = 0; j <= 25; j++)
            lift[i][j] = 0;
    }
    for (int i = 1; i <= M; i++) edges[i] = {0, 0, 0};
    for (int i = 1; i <= N; i++) f[i] = 0;
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