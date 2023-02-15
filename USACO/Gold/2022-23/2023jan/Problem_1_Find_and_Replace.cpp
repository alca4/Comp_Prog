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
int N, Q;
ll L, R;
string nodes[MAXN];
int nbs[MAXN][26];
ll sz[MAXN];
map<char, vector<pii>> contains;

void DFS(int a)
{
    if (sz[a] != 0) return;
    for (int i = 0; i < nodes[a].length(); i++) 
    {
        if (nodes[a][i] <= 90) 
        {
            int nb = nbs[a][nodes[a][i] - 'A'];
            while (nodes[nb].size() == 1 && nodes[nb][0] <= 90)
                nb = nbs[nb][nodes[nb][0] - 'A'];
            nbs[a][nodes[a][i] - 'A'] = nb;
            DFS(nb);
            sz[a] += sz[nb];
            sz[a] = min(sz[a], LINF);
        }
        else 
        {
            sz[a]++;
            sz[a] = min(sz[a], LINF);
        }
    }
    sz[a] = min(sz[a], LINF);
}

ll v;

void findChar(int a, ll s)
{
    for (int i = 0; i < nodes[a].length(); i++)
    {
        if (s > v || v > R) return;
        if (nodes[a][i] <= 90) 
        {
            int nb = nbs[a][nodes[a][i] - 'A'];
            if (v <= s + sz[nb] - 1) findChar(nb, s);
            s += sz[nb];
        }
        else 
        {
            if (s == v) 
            {
                cout << nodes[a][i];
                v++;
                if (v > R) return;
            }
            s++;
        }
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
            nodes[n.FF][n.SS] = toupper(nodes[n.FF][n.SS]);
        }
        contains[s].clear();
        for (int i = 0; i < e.length(); i++) contains[e[i]].pb({N, i});
    }

    DFS(1);

    v = L;
    findChar(1, 1);
    cout << endl;

    return 0;
} 