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
ll INF = 1000000000;
ll MOD = 998244353;

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

// ans = (N - #1s) groups-ate

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll factinv[100010];
    factinv[0] = 1;
    for (int i = 1; i <= 100000; i++) factinv[i] = divide(factinv[i - 1], i);

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        string str;
        cin >> N;
        cin >> str;
        
        ll num_ones = 0;
        ll num_groups = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == '1') 
            {
                num_ones++;
                if (i < str.length() - 1 && str[i + 1] == '1')
                {
                    num_ones++;
                    num_groups++;
                    i++;
                }
            }
        }

        ll ate = N - num_ones + 1;
        ll ans = factinv[num_groups];
        for (int i = ate; i <= ate + num_groups - 1; i++) ans = mult(ans, i);
        cout << ans << endl;
    }
    return 0;
} 