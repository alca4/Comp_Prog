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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 300010;
int N, M, Q;
struct Edge
{
    int a, b, w;
} edgelist[MAXN];

bool operator<(const Edge& e1, const Edge& e2)
{
    return e1.w > e2.w;
}

int in[2 * MAXN], out[2 * MAXN];
int lift[2 * MAXN][32];
int T = 0;

int p[2 * MAXN];
vector<int> nbs[2 * MAXN];
int v[2 * MAXN];
int root(int a)
{
    return p[a] = (a == p[a] ? a : root(p[a]));
}

int combine(const Edge& e)
{
    int a = e.a, b = e.b, w = e.w;
    a = root(a), b = root(b);
    if (a == b) return 0;

    int n = ++N;
    p[a] = p[b] = p[n] = n;
    lift[a][0] = lift[b][0] = n;
    v[n] = w;
    return 1;
}

void DFS(int a, int p)
{
    in[a] = ++T;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
        DFS(nbs[a][i], a);
    out[a] = ++T;
}

bool is_anc(int a, int b)
{
    return in[a] < in[b] && out[b] < out[a];
}

int lca(int a, int b)
{
    if (is_anc(a, b)) return v[a];
    if (is_anc(b, a)) return v[b];

    while (!is_anc(a, b))
    {
        for (int i = 1; i < 32; i++) if (is_anc(lift[a][i], b))
        {
            a = lift[a][i - 1];
            break;
        }
    }

    return v[a];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
        cin >> edgelist[i].a >> edgelist[i].b >> edgelist[i].w;
    
    sort(edgelist + 1, edgelist + 1 + M);

    for (int i = 1; i <= N; i++) p[i] = i;

    int N0 = N;
    for (int i = 1, cnt = 0; i <= M, cnt < N0 - 1; i++)
        cnt += combine(edgelist[i]);
    
    for (int i = 1; i <= N; i++) 
        for (int j = 1; j < 32; j++) lift[i][j] = lift[lift[i][j - 1]][j - 1];
    
    for (int i = 1; i <= N; i++) nbs[p[i]].pb(i);

    for (int i = 1; i <= N; i++) if (p[i] == i) DFS(i, 0);

    cin >> Q;
    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        if (root(a) != root(b)) cout << -1 << endl;
        else cout << lca(a, b) << endl;
    }
    return 0;
} 