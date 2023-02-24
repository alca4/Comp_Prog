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
// ll MOD = 1000000007;
ll MOD = 998244353;

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

const int MAXN = 510;
int N;
int Q, Q2;
int dp[MAXN][MAXN];
int fact[MAXN], factinv[MAXN];
int remsum[MAXN][MAXN];

int choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    fact[0] = 1;
    for (int i = 1; i <= N + 1; i++) fact[i] = mult(fact[i - 1], i);
    factinv[N + 1] = divide(1, fact[N + 1]);
    for (int i = N; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);

    Q2 = divide(10000 - Q, 10000);
    Q = divide(Q, 10000);

    for (int i = 0; i <= N; i++) remsum[0][i] = dp[0][i] = 1;

    for (int i = 1; i <= N; i++) for (int j = 0; j <= N - i; j++)
    {
        for (int k = 0; k < i; k++)
        {
            dp[i][j] = add(dp[i][j], mult(mult(remsum[i - 1 - k][j], dp[k][j + 1]),
                                          mult(Q, mult(fact[i - 1], factinv[k]))));
            if (j > 0) dp[i][j] = add(dp[i][j], mult(mult(remsum[i - 1 - k][j], dp[k][j - 1]),
                                          mult(Q2, mult(fact[i - 1], factinv[k]))));
        }

        for (int k = 0; k <= i; k++)
            remsum[i][j] = add(remsum[i][j], mult(mult(dp[k][j], dp[i - k][j]),
                                                  mult(factinv[k], factinv[i - k])));
    }

    int ans = dp[N][0];
    for (int i = 1; i <= N; i++) ans = divide(ans, 2 * i - 1);
    cout << ans << endl;
    return 0;
} 