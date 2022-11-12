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
#define MOD 123456789ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 1000010;
ll L, S;
ll dp[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> L >> S;
    dp[1] = 1;
    for (int i = 2; i <= L; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 1] - dp[max(0ll, i - S - 1)] + MOD;
        dp[i] %= MOD;
    }

    ll ans = 0;
    for (int i = L; i > L - S; i--) 
    {
        ans += (dp[i] - dp[i - 1] + MOD) * (L - i + 1);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}