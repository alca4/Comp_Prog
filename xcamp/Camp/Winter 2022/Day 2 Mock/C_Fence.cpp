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

const int MAXN = 500010;

int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b, int c)
{
    a = root(a), b = root(b);
    // cout << "combining " << a << " and " << b << " with " << c << endl;
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b] - 2 * c;
    return 1;
}

map<pii, int> id;
int Q, N;

map<int, int> borders(int x, int y)
{
    int dx[6] = {-1, -1, 0, 1, 1, 0};
    int dy[6] = {0, 1, 1, 0, -1, -1};

    map<int, int> nbs;

    for (int i = 0; i < 6; i++)
        if (id.count({x + dx[i], y + dy[i]})) nbs[root(id[{x + dx[i], y + dy[i]}])]++;
    
    return nbs;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> Q;
    while (Q--)
    {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1)
        {
            id[{x, y}] = ++N;
            p[N] = N, sz[N] = 6;

            map<int, int> nbs = borders(x, y);
            for (auto n : nbs) combine(N, n.FF, n.SS);
        }
        if (t == 2) cout << sz[root(id[{x, y}])] << endl;
    }
    return 0;
} 