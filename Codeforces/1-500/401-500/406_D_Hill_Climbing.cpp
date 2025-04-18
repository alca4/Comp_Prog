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
int N, Q;
struct Point
{
    ll x, y;
    int id;

    ll dist(const Point& p)
    {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
} pts[MAXN];

int orientation(const Point& p1, const Point& p2, const Point& p3)
{
    ll v = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

set<int> nbs[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int T = 0;
void tour(int a, int p)
{
    lift[a][0] = p;
    for (int j = 1; j < 32; j++) 
        lift[a][j] = lift[lift[a][j - 1]][j - 1];
    in[a] = ++T;
    euler[T] = a;
    for (auto nb : nbs[a]) if (nb != p) tour(nb, a);
    out[a] = ++T;
    euler[T] = -a;
}
bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
void setup_lca()
{
    tour(N, N);
}
int lca(int a, int b)
{
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = 31; i >= 0; i--)
        if (!is_anc(lift[a][i], b)) a = lift[a][i];
    
    return lift[a][0];
}

int top = 0;
Point s[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    for (int i = N; i >= 1; i--)
    {
        while (top >= 2 && orientation(s[top - 1], s[top], pts[i]) == 1) top--;
        if (top) nbs[s[top].id].insert(i);
        s[++top] = pts[i];
    }

    setup_lca();

    cin >> Q;
    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << " ";
    }
    cout << endl;
    return 0;
} 