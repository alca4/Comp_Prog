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
int N, M;
vector<int> adjlist[MAXN];
map<int, int> families;

bitset<MAXN> b;

int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
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
    {
        int a, b;
        cin >> a >> b;
        adjlist[a].pb(b);
        adjlist[b].pb(a);
    }

    vector<int> g2n;
    for (int i = 1; i <= N; i++)
    {
        if (adjlist[i].size() * 2 <= N - 1) g2n.pb(i);
        else
        {
            for (int j = 0; j < adjlist[i].size(); j++) b[adjlist[i][j]] = 1;
            for (int j = 1; j <= N; j++) if (!b[j])
                combine(i, j);
            b = 0;
        }
    }

    for (int i = 1; i < g2n.size(); i++) 
        combine(g2n[i], g2n[i - 1]);

    for (int i = 1; i <= N; i++) families[root(i)]++;

    vector<int> ans;
    for (auto n : families) ans.pb(n.SS);

    sort(ans.begin(), ans.end());

    cout << ans.size() << endl;
    for (auto n : ans) cout << n << " ";
    cout << endl;
    return 0;
} 