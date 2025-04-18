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

const int MAXN = 110;
int N;
int a[MAXN];
int b[MAXN];
int dp[MAXN][MAXN * MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N;
        for (int i = 1; i <= N; i++) cin >> a[i];
        for (int i = 1; i <= N; i++) cin >> b[i];

        ll totsum = 0;
        ll sqsum = 0;
        for (int i = 1; i <= N; i++) 
        {
            totsum += a[i] + b[i];
            sqsum += a[i] * a[i] + b[i] * b[i];
        }

        dp[0][0] = 1;
        for (int i = 1; i <= N; i++) 
        {
            for (int j = a[i]; j <= 100 * N; j++) 
                if (dp[i - 1][j - a[i]]) dp[i][j] = 1;
            for (int j = b[i]; j <= 100 * N; j++) 
                if (dp[i - 1][j - b[i]]) dp[i][j] = 1;
        }

        ll best = 0;
        for (int i = 0; i <= 100 * N; i++) 
            if (dp[N][i] && abs(totsum - 2 * best) > abs(totsum - 2 * i)) best = i;
        
        cout << max(0ll, (N - 2) * (sqsum) + best * best + (totsum - best) * (totsum - best)) << endl;

        for (int i = 0; i <= N; i++) for (int j = 0; j <= 100 * N; j++) dp[i][j] = 0;
        for (int i = 1; i <= N; i++) a[i] = b[i] = 0;
    }
} 