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
#define MOD 1000000007ll

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

const int MAXN = 60;
int N, K;
string dp[MAXN][MAXN];
string strs[MAXN];

bool Comp(const string& s1, const string& s2)
{
    string c1 = s1 + s2;
    string c2 = s2 + s1;
    return c1 < c2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> strs[i];

    sort(strs + 1, strs + 1 + N, Comp);

    dp[N][1] = strs[N];
    for (int i = N - 1; i >= 1; i--) 
    {
        for (int j = 1; j <= N - i + 1; j++)
        {
            dp[i][j] = min(strs[i] + dp[i + 1][j - 1], dp[i + 1][j]);
            if (dp[i + 1][j] == "") dp[i][j] = strs[i] + dp[i + 1][j - 1];
        }
    }

    cout << dp[1][K] << endl;
    return 0;
} 