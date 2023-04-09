/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
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
#define ull unsigned ll
#define endl "\n"
ll INF = 2000000000;
ll LINF = 9000000000000000000;
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

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

const int MAXN = 1000010;
ll B, S;
int sieve[MAXN];
vector<int> primes;
vector<pll> f;
vector<ll> divs;
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

bool test(ll d)
{
    ll ans = 0;
    ll tmp = B;
    while (tmp > 0)
    {
        ans += tmp % d;
        tmp /= d;
    }
    
    return ans == S;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> B >> S;
    MOD = LINF;
    
    for (int i = 2; i <= 1000000; i++) if (!sieve[i])
    {
        primes.pb(i);
        // cout << i << endl;
        for (int j = 1; i * j <= 1000000; j++) sieve[i * j] = 1;
    }

    ll tmp = B - S;
    for (int i = 0; i < primes.size(); i++)
    {
        int x = 0;
        while (tmp > 1 && tmp % primes[i] == 0)
        {
            x++;
            tmp /= primes[i];
        }
        if (x) f.pb(pll(primes[i], x));
    }
    if (tmp > 1) f.pb(pll(tmp, 1));

    int x = 1;
    for (int i = 0; i < f.size(); i++) x *= (f[i].SS + 1);
    for (int i = 0; i < x; i++)
    {
        int t = i;
        ll v = 1;
        for (int j = 0; j < f.size(); j++) 
        {
            v *= power(f[j].FF, t % (f[j].SS + 1));
            t /= (f[j].SS + 1);
        }
        divs.pb(v + 1);
    }

    sort(divs.begin(), divs.end());

    if (B == S) 
    {
        cout << B + 1 << endl;
        return 0;
    }

    for (ll n : divs) if (test(n)) 
    {
        cout << n << endl;
        return 0;
    }
    cout << -1 << endl;
    return 0;
} 