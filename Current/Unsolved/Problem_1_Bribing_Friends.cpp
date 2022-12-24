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
int N, A, B;
int dp[MAXN][MAXN];
struct F
{
    int p, c, x;
} friends[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) cin >> friends[i].p >> friends[i].c >> friends[i].x;

    for (int k = 1; k <= N; k++) 
        for (int i = 0; i <= A; i++) for (int j = 0; j <= B; j++)
        {
            for (int g = 0; g * friends[k].x <= j; g++)
                if (i - friends[k].c + g <= i && i - friends[k].c + g >= 0)
                {
                    dp[i - friends[k].c + g][j - g * friends[k].x] = 
                        max(dp[i - friends[k].c + g][j - g * friends[k].x], dp[i][j] + friends[k].p);
                }
        }

    int ans = 0;
    for (int i = 0; i <= A; i++) for (int j = 0; j <= B; j++) ans = max(ans, dp[i][j]);

    cout << ans << endl;
    return 0;
} 