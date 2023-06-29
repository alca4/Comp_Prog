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
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = INF;

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
ll binexp[32];
ll power(ll a, ll b) {
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
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

const int MAXN = 0;
int N;

int sieve[1000010];
vector<int> primes;
struct NumberTheory {
    static void get_primes(int x) {
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int n) {
        vector<pii> v;
        for (int p : primes) {
            if (p > n) return;
            v.pb(pii(p, 0));
            while (n % p == 0) {
                v.back().SS++;
                n /= p;
            }
            if (v.back().SS == 0) v.pop_back();
            else v.back().SS++;
        }
        if (n > 1) v.pb(pii(n, 2));
        return v;
    }

    static int num_div(int n) {
        int x = 1;
        for (pii p : factorize(n)) x *= p.SS;
        return x;
    }

    static vector<int> gen_div(int n) {
        vector<pii> v = factorize(n);
        int x = 1;
        for (pii p : v) x *= p.SS;
        vector<int> divs;
        for (int i = 0; i < x; i++) {
            int t = i;
            int d = 1;
            for (pii p : v) {
                if (t % p.SS) d *= power(p.FF, t % p.SS);
                t /= p.SS;
            }
            divs.pb(d);
        }
        return divs;
    }
};

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    NumberTheory::get_primes(1000000);
    cin >> N;
    

    return 0;
} 