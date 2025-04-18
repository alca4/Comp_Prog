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

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> primes;
    int sieve[200010];
    for (int i = 2; i <= 200000; i++) 
    {
        if (!sieve[i]) 
        {
            primes.pb(i);
            for (int j = i; j <= 200000; j += i) sieve[i] = 1;
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int a, b;
        cin >> a >> b;

        if (a % b != 0) 
        {
            cout << -1 << endl;
            continue;
        }

        int arr[200010];
        for (int i = 1; i <= a; i++) arr[i] = i;

        arr[1] = b;

        int i = b;
        for (int j = 0; j < primes.size(); j++)
        {
            if (i * primes[j] > a) break;
            while (a % (i * primes[j]) == 0) 
            {
                arr[i] = i * primes[j];
                i *= primes[j];
            }
        }
        arr[i] = a;
        arr[a] = 1;

        for (int i = 1; i <= a; i++) cout << arr[i] << " ";
        cout << endl;
    }

    return 0;
} 