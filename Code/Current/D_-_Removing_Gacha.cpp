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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
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

const int MAXN = 200010;
int N;
vector<int> nbs[MAXN];
int depth[MAXN];
ll dp[MAXN][2];

void DFS(int a, int d)
{
    depth[d]++;
    for (int i = 0; i < nbs[a].size(); i++) DFS(nbs[a][i], d + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 2; i <= N; i++)
    {
        int a;
        cin >> a;
        nbs[a].pb(i);
    }

    DFS(1, 1);

    dp[0][0] = 0;
    dp[0][1] = 1;
    for (int i = 1; i <= N; i++)
    {
        dp[i][0] = add(mult(dp[i][1], modInverse(i + 1)),
                       mult(dp[i - 1][0], mult(i, modInverse(i + 1))));
        dp[i][1] = add(modInverse(i),
                       mult(dp[i - 1][1], mult(i, modInverse(i + 1))));
    }

    // for (int i = 0; i < N; i++) cout << depth[i] << endl;

    ll ans = 0;
    for (int i = 1; i <= N; i++) ans = add(ans, mult(depth[i], add(dp[i][0], dp[i][1])));
    cout << ans << endl;
    return 0;
} 