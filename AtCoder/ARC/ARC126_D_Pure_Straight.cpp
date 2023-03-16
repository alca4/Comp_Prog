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

const int MAXN = 210, MAXK = 16;
int N, K;
int arr[MAXN];
int dp[MAXN][(1 << MAXK)];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) arr[i]--;

    for (int i = 0; i <= N; i++) for (int mask = 0; mask < (1 << K); mask++)
        dp[i][mask] = INF;
    
    dp[0][0] = 0;
    for (int i = 1; i <= N; i++) for (int mask = 0; mask < (1 << K); mask++) 
    {
        if ((mask & (1 << arr[i])) && dp[i - 1][mask & ~(1 << arr[i])] != INF)
        {
            int cost = 0;

            int nb = 0;
            int gb = 0;
            for (int j = 0; j < K; j++) if (j != arr[i])
            {
                if (mask & (1 << j)) 
                {
                    nb++;
                    if (j > arr[i]) gb++;
                }
            }

            if (nb <= (K - 1) / 2) 
            {
                cost += -i - ((K - 1) / 2 - nb);
                if (nb == (K - 1) / 2) if (K % 2) cost += i;
            }
            else if (nb > (K - 1) / 2) cost += i - (nb - (K - 1) / 2);
            cost += gb;

            // cout << nb << " " << gb << endl;

            dp[i][mask] = min(dp[i][mask], dp[i - 1][mask & ~(1 << arr[i])] + cost);
            // cout << i - 1 << " " << (mask & ~(1 << arr[i])) << " to " 
            //     << i << " " << mask << " with cost " << cost << endl;
        }
        if (dp[i - 1][mask] != INF) dp[i][mask] = min(dp[i][mask], dp[i - 1][mask]);
        // if (dp[i][mask] != INF) cout << i << " " << mask << " " << dp[i][mask] << endl;
    }

    int ans = INF;
    for (int i = 1; i <= N; i++) 
    {
        ans = min(ans, dp[i][(1 << K) - 1]);
        // cout << dp[i][(1 << K) - 1] << endl;
    }
    cout << ans << endl;
    return 0;
} 