#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define INF 2000000000

const int MAXN = 600010;

int N, M;
struct Edge
{
    int x, y, w;
} edges[MAXN];

bool CompW(const Edge& e1, const Edge& e2)
{
    return e1.w < e2.w;
}

int extra;
int p[MAXN];
vector<int> child[MAXN];
int nbs[MAXN];
int is_chain[MAXN];
int bnc[MAXN];
int w[MAXN];

int root(int a)
{
    int ans = (a == p[a] ? a : root(p[a]));
    return p[a] = ans;
}

void combine(int n1, int n2, int e)
{
    int rn1 = root(n1);
    int rn2 = root(n2);
    nbs[n1]++;
    nbs[n2]++;
    w[extra] = e;
    if (rn1 != rn2)
    {
        p[rn1] = p[rn2] = p[extra] = extra;
        child[extra].push_back(rn1);
        child[extra].push_back(rn2);
        is_chain[extra] = (nbs[n1] <= 2 && nbs[n2] <= 2 && is_chain[rn1] && is_chain[rn2]);
    }
    else
    {
        p[rn1] = p[extra] = extra;
        child[extra].push_back(rn1);
        is_chain[extra] = 0;
    } 
    extra++;
}

int up[MAXN][30];
int t = 0;
int tin[MAXN];
int tout[MAXN];

void DFS(int n, int p)
{
    tin[n] = t++;
    up[n][0] = p;
    bnc[n] = bnc[p];
    if (!is_chain[n]) bnc[n] = n;
    for (int i = 0; i < 25; i++)
        up[n][i + 1] = up[up[n][i]][i];
    for (int i = 0; i < (int) child[n].size(); i++)
    {
        if (child[n][i] == p) continue;
        DFS(child[n][i], n);
    }
    tout[n] = t++;
}

int is_anc(int n1, int n2)
{
    return tin[n1] <= tin[n2] && tout[n2] <= tout[n1];
}

int getMinimumFuelCapacity(int c1, int c2)
{
    if (is_anc(c1, c2)) 
    {
        if (bnc[c1] == INF) return -1;
        return w[bnc[c1]];
    }
    if (is_anc(c2, c1))
    {
        if (bnc[c2] == INF) return -1;
        return w[bnc[c2]];
    }
    
    for (int i = 25; i >= 0; i--)
    {
        if (!is_anc(up[c1][i], c2))
            c1 = up[c1][i];
    }

    int anc = up[c1][0]; 
    if (bnc[anc] == INF) return -1;
    return w[bnc[anc]];
}

void init(int n, int m, vector<int> U, vector<int> V, vector<int> W)
{
    extra = N = n;
    M = m;
    for (int i = 0; i < M; i++) edges[i] = {U[i], V[i], W[i]};
    for (int i = 0; i < N; i++) is_chain[i] = 1, p[i] = i;

    sort(edges, edges + M, CompW);
    for (int i = 0; i < M; i++) combine(edges[i].x, edges[i].y, edges[i].w);

    bnc[extra - 1] = INF;
    DFS(extra - 1, extra - 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    vector<int> u(M), v(M), w(M);
    for (int i = 0; i < M; i++) cin >> u[i] >> v[i] >> w[i];
    init(N, M, u, v, w);
    int Q;
    cin >> Q;
    while (Q--)
    {
        int n1, n2;
        cin >> n1 >> n2;
        cout << getMinimumFuelCapacity(n1, n2) << endl;
    }
}