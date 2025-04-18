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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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

/*
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[i]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}
*/

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        ll a, b;
        cin >> a >> b;

        int num2 = 0;
        int num5 = 0;

        ll ta = a, tb = b;
        while (ta % 2 == 0)
        {
            ta /= 2;
            num2++;
        }
        while (ta % 5 == 0)
        {
            ta /= 5;
            num5++;
        }

        int v = 0;
        while (num2 > num5 && b >= 5)
        {
            b /= 5;
            a /= 2;
            v++;
            num5++;
        }
        while (num5 > num2 && b >= 2)
        {
            b /= 2;
            a /= 5;
            v++;
            num2++;
        }

        // cout << a << " " << b << endl;

        int cnt = 0;
        while (b >= 10)
        {
            b /= 10;
            cnt++;
        }
        while (cnt)
        {
            b *= 10;
            cnt--;
        }

        ll x = a * b;
        for (int i = 0; i < v; i++) x *= 10;
        cout << x << endl;
    }

    return 0;
} 