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

const int MAXN = 2010;
int N, M, P;
pii pts[MAXN];

ll fact[200010];
ll factinv[200010];
ll choose(int a, int b) {return mult(fact[a], mult(factinv[b], factinv[a - b]));}
ll value[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P;
    fact[0] = factinv[0] = 1;
    for (int i = 1; i <= 200000; i++) fact[i] = mult(fact[i - 1], i);
    for (int i = 1; i <= 200000; i++) factinv[i] = divide(factinv[i - 1], i);

    for (int i = 1; i <= P; i++) cin >> pts[i].FF >> pts[i].SS;

    sort(pts + 1, pts + 1 + P, [](const pii& p1, const pii& p2)
    {
        return p1.FF + p1.SS < p2.FF + p2.SS;
    });

    for (int i = 1; i <= P; i++) value[i] = choose(pts[i].FF - 1 + pts[i].SS - 1, pts[i].FF - 1);

    ll ans = choose(N - 1 + M - 1, N - 1);

    for (int i = 1; i <= P; i++)
    {
        ans = sub(ans, mult(choose(N - pts[i].FF + M - pts[i].SS, N - pts[i].FF), value[i]));
        for (int j = i + 1; j <= P; j++) if (pts[j].FF >= pts[i].FF && pts[j].SS >= pts[i].SS) 
            value[j] = sub(value[j], mult(choose(pts[j].FF - pts[i].FF + 
                                          pts[j].SS - pts[i].SS, pts[j].FF - pts[i].FF), value[i]));
    }

    cout << ans << endl;
    return 0;
} 