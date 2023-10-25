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
ll MOD = 1000000007;

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

const int MAXN = 200010;
int N;
int sieve[MAXN];
vector<int> primes;
int arr[MAXN];
map<int, int> occ;
map<int, vector<pii>> divisors;
map<int, int> v;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 2; i <= 10000; i++)
    {
        if (!sieve[i])
        {
            primes.pb(i);
            for (int j = 1; i * j <= 10000; j++) sieve[i * j] = 1;
        }
    }

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= N; i++) 
    {
        if (occ.count(arr[i])) 
        {
            occ[arr[i]]++;
            continue;
        }
        int tmp = arr[i];
        for (int j = 0; j < primes.size(); j++)
        {
            if (primes[j] * primes[j] > tmp) break;
            int x = 0;
            while (tmp % primes[j] == 0)
            {
                tmp /= primes[j];
                x++;
            }
            if (x != 0) divisors[arr[i]].pb({primes[j], x});
        }
        if (tmp != 1) divisors[arr[i]].pb({tmp, 1});
        occ[arr[i]]++;
    }

    int ok = 1;
    for (int i = 1; i <= N; i++)
    {
        int numdiv = 1;
        for (int j = 0; j < divisors[arr[i]].size(); j++)
            numdiv *= (divisors[arr[i]][j].SS + 1);
        if (occ[arr[i]] > numdiv) ok = 0;
    }
    
    if (!ok) cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        for (int i = 1; i <= N; i++)
        {
            int x = v[arr[i]];
            int d = 1;
            for (int j = 0; j < divisors[arr[i]].size(); j++)
            {
                d *= pow(divisors[arr[i]][j].FF, (x % (divisors[arr[i]][j].SS + 1)));
                x /= (divisors[arr[i]][j].SS + 1);
            }
            v[arr[i]]++;
            cout << d << " " << arr[i] / d << endl;
        }
    }

    return 0;
} 