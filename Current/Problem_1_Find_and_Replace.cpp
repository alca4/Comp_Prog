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
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

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

const int MAXN = 200010;
int N, L, R, Q;
string nodes[MAXN];
int nbs[MAXN][26];
int sz[MAXN];
set<pair<pii, int>> ranges[MAXN];
map<char, vector<pii>> contains;

void DFS(int a)
{
    if (sz[a] != 0) return;
    for (int i = 0; i < nodes[a].length(); i++) 
    {
        if (nodes[a][i] <= 90) 
        {
            DFS(nbs[a][nodes[a][i] - 'A']);
            sz[a] += sz[nbs[a][nodes[a][i] - 'A']];
        }
        else 
        {
            // ranges.insert({{sz[a] + 1, sz[a] + 1}, })
            // sz[a]++;
        }
    }
}

void findChar(int a, int l, int r, int v)
{
    if (v < l || v > r) return;
    int s = l;
    for (int i = 0; i < nodes[a].length(); i++)
    {
        if (s > v) 
        if (nodes[a][i] <= 90) 
        {
            int nb = nbs[a][nodes[a][i] - 'A'];
            findChar(nb, s, s + sz[nb] - 1, v);
            s += sz[nb];
        }
        else s++;
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> L >> R >> Q;
    nodes[++N] = "a";
    contains['a'].pb({1, 0});
    while (Q--)
    {
        char s;
        string e;
        cin >> s >> e;
        nodes[++N] = e;
        for (auto n : contains[s]) 
        {
            nbs[n.FF][nodes[n.FF][n.SS] - 'a'] = N;
            // cout << n.FF << " at " << nodes[n.FF][n.SS] << " goes to " << N << endl;
            nodes[n.FF][n.SS] = toupper(nodes[n.FF][n.SS]);
        }
        contains[s].clear();
        for (int i = 0; i < e.length(); i++) contains[e[i]].pb({N, i});
    }

    DFS(1);

    findChar()

    return 0;
} 