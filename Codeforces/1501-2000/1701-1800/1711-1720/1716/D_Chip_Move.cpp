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
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ll
#define MOD 998244353

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 200010;
int N, K;
ll dp[MAXN];
ll ans[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    dp[0] = 1;
    int s = 0;
    for (int i = K; s + i <= N; i++)
    {
        vector<ll> tmpsum(i);
        for (int j = s; j <= N; j++)
        {
            ll tmp = dp[j];
            dp[j] = tmpsum[j % i];
            ans[j] += dp[j];
            ans[j] %= MOD;
            tmpsum[j % i] += tmp;
            tmpsum[j % i] %= MOD;
        }
        s += i;
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
} 