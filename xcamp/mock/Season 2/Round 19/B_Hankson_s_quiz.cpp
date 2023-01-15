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

int sieve[100010];
vector<int> primes;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 2; i <= 100000; i++)
    {
        if (!sieve[i])
        {
            primes.pb(i);
            for (int j = i; j <= 100000; j += i) sieve[j] = 1;
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;

        set<int> nums;
        for (int i = 1; i <= 100000; i++) if (b1 % i == 0)
        {
            nums.insert(i);
            nums.insert(b1 / i);
        }

        int ans = 0;
        for (auto n : nums)
        {
            if (gcd(n, a0) == a1 && n / gcd(n, b0) * b0 == b1)
                ans++;
        }

        cout << ans << endl;
    }

    return 0;
} 