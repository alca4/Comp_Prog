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

const int MAXN = 310;
int N;
pii points[MAXN];
int lines[MAXN][MAXN];
int triangles[MAXN];
map<int, int> freq;

int sign(ll a) {return (a > 0) - (a < 0);}
ll cp(pii p1, pii p2) 
{
    return 1ll * p1.FF * p2.SS - 1ll * p1.SS * p2.FF;
}
int orientation(pii p1, pii p2, pii p3)
{
    return sign(cp(pii(p2.FF - p1.FF, p2.SS - p1.SS), pii(p3.FF - p2.FF, p3.SS - p2.SS)));
}

int main()
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> points[i].FF >> points[i].SS;

    sort(points + 1, points + 1 + N);
    
    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) 
    {
        int ans = 0;
        for (int k = 1; k <= N; k++) 
        {
            if (points[k].FF >= points[j].FF && points[k].FF <= points[i].FF &&
                orientation(points[i], points[k], points[j]) < 0)
                ans++;
        }
        lines[i][j] = lines[j][i] = ans;
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) for (int k = 1; k < j; k++)
    {
        int x;
        if (orientation(points[i], points[j], points[k]) > 0)
        {
            x = lines[i][j] + lines[j][k] - lines[i][k];
            if (points[j - 1].FF == points[j].FF) x--;
        }
        else
        {
            x = lines[i][k] - lines[i][j] - lines[j][k] - 1;
            if (points[j - 1].FF == points[j].FF) x++;
        }

        triangles[x]++;
    }

    for (int i = 0; i <= N - 3; i++) cout << triangles[i] << endl;

    return 0;
} 