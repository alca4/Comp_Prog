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

const int MAXN = 110, MAXM = 1010;
int N;
int arr[MAXN];
ll dp[MAXN][MAXM];

ll solve()
{
    for (int i = 1; i <= N; i++) for (int j = 0; j <= 1000; j++) dp[i][j] = 0;
    for (int i = 0; i <= 1000; i++) dp[0][i] = 1;

    for (int i = 1; i <= N; i++) 
    {
        for (int j = 0; j <= 1000; j++)
        {
            if (arr[i] >= j) 
                dp[i][j] = add(dp[i][j], dp[i - 1][arr[i] - j]);
            if (j > 0) dp[i][j] = add(dp[i][j], dp[i][j - 1]);
        }
    }

    return dp[N][0];
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll ans = 0;
    if (N % 2)
    {
        bool cont = 1;
        for (int i = 1; i <= 1000; i++)
        {
            if (cont) ans = add(ans, solve());
            for (int j = 1; j <= N; j++) 
            {
                arr[j]--;
                if (arr[j] < 0) cont = 0;
            }
        }
    }
    else ans = solve();

    cout << ans << endl;
    return 0;
} 