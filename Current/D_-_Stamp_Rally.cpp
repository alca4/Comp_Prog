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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 100010;
int N, M, Q;

struct Query
{
    int n1, n2, z;
} queries[MAXN];
int ans[MAXN];
pii edgelist[MAXN];

stack<pii> edges;
int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return a == p[a] ? a : root(p[a]);}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;
    if (sz[a] > sz[b]) swap(a, b);
    edges.push({a, b});

    p[a] = b;
    sz[b] += sz[a];

    return 1;
}
void undo()
{
    int a = edges.top().FF;
    int b = edges.top().SS;
    edges.pop();

    sz[b] -= sz[a];
    p[a] = a;
}

/*
Precondition: 1 to l - 1 are in the dsu, l to M 
*/
void pbs(int l, int r, vector<int>& ids)
{
    if (ids.size() == 0) return;
    if (l == r)
    {
        for (int i = 0; i < ids.size(); i++) ans[ids[i]] = l;
        return;
    }

    int mid = (l + r) / 2;
    int good = 0;
    for (int i = l; i <= mid; i++) good += combine(edgelist[i].FF, edgelist[i].SS);
    
    vector<int> lid;
    vector<int> rid;
    for (int i = 0; i < ids.size(); i++) 
    {
        int x = root(queries[ids[i]].n1);
        int y = root(queries[ids[i]].n2);

        int n = sz[x];
        if (x != y) n += sz[y];
        
        if (n >= queries[ids[i]].z) lid.pb(ids[i]);
        else rid.pb(ids[i]);
    }

    pbs(mid + 1, r, rid);
    for (int i = 1; i <= good; i++) undo();
    pbs(l, mid, lid);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    setup_dsu();
    for (int i = 1; i <= M; i++)
        cin >> edgelist[i].FF >> edgelist[i].SS;

    cin >> Q;
    for (int i = 1; i <= Q; i++) 
        cin >> queries[i].n1 >> queries[i].n2 >> queries[i].z;
    
    vector<int> ids;
    for (int i = 1; i <= Q; i++) ids.pb(i);
    pbs(1, M, ids);

    for (int i = 1; i <= Q; i++) cout << ans[i] << endl;
    return 0;
} 