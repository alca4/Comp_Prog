/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 200010;
int N, M;
ll w[MAXN * 2];
struct Edge
{
    int a, b, w;

    bool operator<(Edge& other)
    {
        return w < other.w;
    }
} edgelist[MAXN];
int dp[2 * MAXN];
vector<pii> nbs[2 * MAXN];
int p[2 * MAXN];
int p0[2 * MAXN];

int rt(int a) {return p[a] = (a == p[a] ? a : rt(p[a]));}
bool combine(Edge& e)
{
    int a = rt(e.a);
    int b = rt(e.b);
    if (a == b) return 0;

    N++;
    
    w[N] = w[a] + w[b];
    nbs[N].pb({a, e.w});
    nbs[N].pb({b, e.w});
    p[a] = p[b] = p[N] = N;
    p0[a] = p0[b] = e.w;
    return 1;
}

void DFS(int a, int v)
{
    dp[a] &= v;
    for (int i = 0; i < nbs[a].size(); i++) DFS(nbs[a][i].FF, dp[a]);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    int N0 = N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> w[i];
        p[i] = i;
    }
    for (int i = 1; i <= M; i++)
    {
        cin >> edgelist[i].a >> edgelist[i].b;
        edgelist[i].w = max(w[edgelist[i].a], w[edgelist[i].b]);
    }

    sort(edgelist + 1, edgelist + 1 + M);
    for (int i = 1, cnt = 0; i <= M, cnt < N0 - 1; i++)
        if (combine(edgelist[i])) cnt++;

    dp[N] = 1;
    for (int i = 1; i < N; i++) if (w[i] >= p0[i]) dp[i] = 1;
    DFS(N, 1);
    for (int i = 1; i <= N0; i++) cout << dp[i];
    cout << endl;
    return 0;
}