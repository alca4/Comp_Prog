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
ll INF = 1000000000000000000;
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

const int MAXN = 150010, MAXM = 310;
pll vals[MAXM];
int N, M, D;
ll dp[MAXN];
ll tmp[MAXN];

deque<pll> window;

void insert(ll dpv, int a)
{
    while (!window.empty() && (window.back().FF > dpv)) window.pop_back();
    window.push_back({dpv, a});
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll bs = 0;
    cin >> N >> M >> D;
    for (int i = 1; i <= M; i++) 
    {
        int a, b, t;
        cin >> a >> b >> t;
        vals[i] = {a, t};
        bs += b;
    }

    ll t = 1;
    for (int i = 1; i <= M; i++)
    {
        ll d = min((vals[i].SS - t) * D, 1ll * N);
        for (int j = 1; j <= d; j++)
            insert(dp[j], j);
        
        for (int j = 1; j <= N; j++)
        {
            if (j + d <= N) insert(dp[j + d], j + d);
            dp[j] = window.front().FF + abs(vals[i].FF - j);

            if (j - d == window.front().SS) window.pop_front();
        }

        window.clear();
        t = vals[i].SS;
    }

    ll ans = INF;
    for (int i = 1; i <= N; i++) ans = min(ans, dp[i]);
    cout << bs - ans << endl;
    return 0;
} 