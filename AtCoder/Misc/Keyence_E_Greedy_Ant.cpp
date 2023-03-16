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
void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}

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

const int MAXN = 410;
int N;
ll arr[MAXN];
ll dp[MAXN][MAXN][MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    dp[0][N + 1][1] = 1;
    for (int i = N + 1; i >= 2; i--)
    {
        for (int j = 0; j <= N + 1 - i; j++)
        {
            int s = j, e = j + i;
            for (int k = 0; k <= N; k++)
            {
                if (!dp[s][e][k]) continue;
                if (k > N % 2 && arr[s] < arr[e - 1])
                    maxeq(dp[s][e - 1][k - 1], dp[s][e][k]);
                if (k > N % 2 && arr[s + 1] > arr[e])
                    maxeq(dp[s + 1][e][k - 1], dp[s][e][k]);
                
                maxeq(dp[s + 1][e][k + 1], add(dp[s][e][k], arr[s + 1]));
                maxeq(dp[s][e - 1][k + 1], add(dp[s][e][k], arr[e - 1]));
            }
        }
    }

    for (int i = 1; i <= N + 1; i++) cout << dp[i - 1][i][N % 2 + 1] - 1 << endl;
    return 0;
} 