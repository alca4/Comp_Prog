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
ll MOD = 0;

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
ll power(ll a, ll b)
{
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

struct Poly {
    vector<ll> poly;

    static void dft(vector<ll>& a, int tot, bool inv) {
        ll w[(1 << 17)];
        ll g = 3;
        if (inv) g = power(g, MOD - 2);
        int sz = (1 << tot);

        for (int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;

            if (i < j) swap(a[i], a[j]);
        }

        for (int i = 0; i < tot; i++) {
            w[0] = 1;
            ll t = power(g, (MOD - 1) / (1 << (i + 1)));
            for (int j = 1; j < (1 << i); j++) w[j] = (w[j - 1] * t) % MOD;
            for (int j = 0; j < sz; j += (1 << (i + 1))) {
                for (int k = 0; k < (1 << i); k++) {
                    ll v = (w[k] * a[j + k + (1 << i)]) % MOD;
                    ll f = (a[j + k] + v) % MOD;
                    ll s = (a[j + k] + MOD - v) % MOD;
                    a[j + k] = f;
                    a[j + k + (1 << i)] = s;
                }
            }
        }

        if (inv) {
            ll szinv = power(sz, MOD - 2);
            for (int i = 0; i < sz; i++) a[i] = (a[i] * szinv) % MOD;
        }
    }

    static vector<ll> mult(vector<ll>& a, vector<ll>& b) {
        ll g = 3;
        int tot = 32 - __builtin_clz(a.size() + b.size() - 1);
        if (a.size() == 1 && b.size() == 1) tot = 0;
        int sz = (1 << tot);

        while (a.size() < sz) a.pb(0);
        while (b.size() < sz) b.pb(0);

        dft(a, tot, 0);
        dft(b, tot, 0);

        vector<ll> c(sz);
        for (int i = 0; i < sz; i++) c[i] = (a[i] * b[i]) % MOD;
        dft(c, tot, 1);
        return c;
    }

    static void invert(vector<ll>& f, vector<ll>& g, int n) {
        if (n == 1) {
            g.pb(f[0]);
            return;
        }

        invert(f, g, n - 1);

        vector<ll> t1 = g;
        for (int i = 0; i < f.size(); i++) t1[i] = (t1[i] * 2) % MOD;
        vector<ll> t2 = g;
        vector<ll> t3 = g;
        // fft(fft());
        // for (int i = 0; i < tmp.size(); i++)
    }
};