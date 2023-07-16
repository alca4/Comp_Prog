/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 100010;
int N, K;
int f[MAXN];
ll g[MAXN][450];
ll choose[2 * MAXN];
ll binexp[33];

ll mult(ll a, ll b) {return (a * b) % MOD;}

ll modInverse(int m)
{
    // cout << m << endl;
    binexp[0] = m;
    for (int i = 1; i <= 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    ll ans = 1;
    int a = MOD - 2;
    while (a)
    {
        ans = mult(ans, binexp[(int) log2(a & -a)]);
        a -= a & -a;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;

    choose[N - 1] = 1;
    for (int i = N; i <= N - 1 + K; i++)
    {
        choose[i] = choose[i - 1];
        choose[i] = mult(choose[i], i);
        choose[i] = mult(choose[i], modInverse(i - N + 1));
    }

    ll ans = 0;
    g[0][0] = 1;
    for (int i = 0; i <= K; i++)
        for (int j = 0; j <= sqrt(2 * K); j++)
        {
            if (j > 0)
            {
                if (i >= j) g[i][j] += g[i - j][j] + g[i - j][j - 1];
                if (i >= N + 1) g[i][j] -= g[i - (N + 1)][j - 1];
                g[i][j] += MOD;
                g[i][j] %= MOD;
            }
            ll temp = mult(g[i][j], choose[K - i + N - 1]);
            if (j % 2) temp *= -1;
            ans += temp + MOD;
            ans %= MOD;
        }
    
    cout << ans << endl;
    return 0;
}