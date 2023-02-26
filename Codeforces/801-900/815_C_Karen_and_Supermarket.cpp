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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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

const int MAXN = 5010;
int N, B;
int c[MAXN], d[MAXN], sz[MAXN];
int dp[MAXN][MAXN];
int dp2[MAXN][MAXN];
vector<int> nbs[MAXN];

/*
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[i]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}
*/

void DFS(int a)
{
    for (int i = 0; i <= N; i++) dp[a][i] = dp2[a][i] = INF + 10;
    dp[a][0] = 0;
    dp[a][1] = c[a];
    dp2[a][1] = c[a] - d[a];
    sz[a] = 1;
    for (int i = 0; i < nbs[a].size(); i++)
    {
        int nb = nbs[a][i];
        DFS(nb);

        for (int j = sz[a]; j >= 0; j--) for (int k = 0; k <= sz[nb]; k++)
        {
            dp[a][j + k] = min(dp[a][j + k], dp[a][j] + dp[nb][k]);
            dp2[a][j + k] = min(dp2[a][j + k], dp2[a][j] + dp2[nb][k]);
            dp2[a][j + k] = min(dp2[a][j + k], dp2[a][j] + dp[nb][k]);
        }
        
        sz[a] += sz[nb];
    }
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> B;
    for (int i = 1; i <= N; i++)
    {
        int n;
        cin >> c[i] >> d[i];
        if (i > 1)
        {
            cin >> n;
            nbs[n].pb(i);
        }
    }

    DFS(1);

    for (int i = N; i >= 0; i--) if (min(dp[1][i], dp2[1][i]) <= B)
    {
        cout << i << endl;
        break;
    }
    return 0;
} 