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

const int MAXN = 200010;
int N;
int arr[MAXN];
ll dp[MAXN];

ll fact[1000010];
ll factinv[1000010];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

ll sb(int a, int b)
{
    return choose(a + b, b);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fact[0] = 1;
    for (int i = 1; i <= 1000000; i++) fact[i] = mult(fact[i - 1], i);
    factinv[1000000] = divide(1, fact[1000000]);
    for (int i = 1000000; i >= 1; i--) factinv[i - 1] = mult(factinv[i], i);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        arr[i] /= 2;
    }

    dp[N] = 1;
    for (int i = N - 1; i >= 1; i--)
    {
        if (arr[i] >= arr[i + 1])
        {
            // int x = arr[i] - (arr[i + 1] - 1);
            // cout << arr[i] - arr[i + 1] + 1 << " " << arr[i + 1] + 1 << endl;
            dp[i] = (dp[i + 1] * sb(arr[i] - arr[i + 1], arr[i + 1])) % MOD;
        }
        else dp[i] = (dp[i + 1] * choose(arr[i + 1] - 1, arr[i] - 1)) % MOD;
    }

    cout << dp[1] << endl;
    return 0;
} 