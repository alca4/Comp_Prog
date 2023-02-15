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

const int MAXN = 90;
int N;
pii pts[MAXN];
ll dp[MAXN][MAXN][MAXN];
int lines[MAXN][MAXN];
int interior[MAXN][MAXN][MAXN];
int area[MAXN][MAXN][MAXN];

int sign(ll a) {return (a > 0) - (a < 0);}
ll cp(pii p1, pii p2) {return 1ll * p1.FF * p2.SS - 1ll * p1.SS * p2.FF;}
int orientation(pii p1, pii p2, pii p3) 
{
    return sign(cp(pii(p2.FF - p1.FF, p2.SS - p1.SS), pii(p3.FF - p2.FF, p3.SS - p2.SS)));
}
int dist(const pii& p1, const pii& p2)
{
    return (p1.FF - p2.FF) * (p1.FF - p2.FF) + (p1.SS - p2.SS) * (p1.SS - p2.SS);
}

void find_interior_points()
{
    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) 
    {
        int ans = 0;
        for (int k = 1; k <= N; k++) 
        {
            if (pts[k].FF >= pts[j].FF && pts[k].FF <= pts[i].FF &&
                orientation(pts[i], pts[k], pts[j]) < 0)
                ans++;
        }
        lines[j][i] = ans;
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) for (int k = 1; k < j; k++)
    {
        int x;
        if (orientation(pts[i], pts[j], pts[k]) > 0)
        {
            x = lines[j][i] + lines[k][j] - lines[k][i];
            if (pts[j - 1].FF == pts[j].FF) x--;
        }
        else
        {
            x = lines[k][i] - lines[k][j] - lines[j][i] - 1;
            if (pts[j - 1].FF == pts[j].FF) x++;
        }

        interior[k][j][i] = x;
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> pts[i].FF >> pts[i].SS;

    sort(pts + 1, pts + 1 + N);

    find_interior_points();

    

    ll ans = 0;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) if (i != j)
    {
        ans += dp[i][j][i];
        if (ans >= MOD) ans -= MOD;
    }

    cout << ans << endl;
    return 0;
} 

/*
positive is counterclockwise, negative is clockwise
*/