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
ll MOD = 998244353;

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
ll w[(1 << 25)];

struct Poly {
    static vector<ll> elemental_op(vector<ll> a, vector<ll> b, int t) {
        int sz = max(a.size(), b.size());
        a.resize(sz);
        b.resize(sz);
        vector<ll> ans(sz);
        for (int i = 0; i < sz; i++) {
            if (t == 0) ans[i] = a[i] + b[i];
            if (t == 1) ans[i] = MOD + a[i] - b[i];
            if (t == 2) ans[i] = a[i] * b[i];
            ans[i] %= MOD;
        }
        return ans;
    }
    
    static void dft(vector<ll>& a, int tot, bool inv) {
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

    static vector<ll> pmult(vector<ll> a, vector<ll> b) {
        int tot = 32 - __builtin_clz(a.size() + b.size() - 1);
        if (a.size() == 1 && b.size() == 1) tot = 0;
        int sz = (1 << tot);

        a.resize(sz);
        b.resize(sz);

        dft(a, tot, 0);
        dft(b, tot, 0);

        vector<ll> c(sz);
        for (int i = 0; i < sz; i++) c[i] = (a[i] * b[i]) % MOD;
        dft(c, tot, 1);
        c.resize(a.size() + b.size() - 1);
        return c;
    }

    static vector<ll> invert(vector<ll> f, int n) {
        if (n == 1) {
            vector<ll> g;
            g.pb(power(f[0], MOD - 2));
            return g;
        }

        vector<ll> g = invert(f, n / 2);

        vector<ll> t1 = g;
        
        for (int i = 0; i < t1.size(); i++) {
            t1[i] *= 2;
            t1[i] %= MOD;
        }
        vector<ll> t2 = g;
        vector<ll> t3 = f;
        t3.resize(n);
        t2 = pmult(t2, t2);
        t2.resize(n);
        t2 = pmult(t2, t3);

        g.resize(n);
        for (int i = 0; i < n; i++) {
            g[i] = MOD;
            if (t1.size() > i) g[i] += t1[i];
            if (t2.size() > i) g[i] -= t2[i];
            g[i] %= MOD;
        }
        return g;
    }

    static vector<ll> integral(vector<ll> f) {
        f.resize(f.size() + 1);
        for (int i = f.size() - 2; i >= 0; i--) {
            f[i + 1] = divide(f[i], i + 1);
            f[i] = 0;
        }
        return f;
    }
    
    static vector<ll> derivative(vector<ll> f) {
        f[0] = 0;
        for (int i = 1; i < f.size(); i++) {
            f[i - 1] = f[i] * i;
            f[i - 1] %= MOD;
            f[i] = 0;
        }
        return f;
    }

    static vector<ll> exp(vector<ll> f, int n) {
        if (n == 1) {
            vector<ll> g;
            g.pb(1);
            return g;
        }
        
        vector<ll> g = exp(f, n / 2);
        vector<ll> tg = g;
        tg.resize(n);
        tg = ln(tg);

        vector<ll> h(n);
        h[0] = 1;
        for (int i = 0; i < n; i++) {
            if (f.size() > i) h[i] += f[i];
            if (tg.size() > i) h[i] += MOD - tg[i];
            h[i] %= MOD;
        }
        h = pmult(h, g);
        h.resize(n);
        return h;
    }

    static vector<ll> ln(vector<ll> f) {
        vector<ll> ans;
        ans = pmult(derivative(f), invert(f, Poly::buffer(f)));
        ans.resize(f.size());
        ans = integral(ans);
        ans.resize(f.size());
        return ans;
    }

    static int buffer(vector<ll> f) {
        return (1 << (32 - __builtin_clz(f.size() - 1)));
    }
};

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    vector<ll> vec;
    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        vec.pb(n);
    }

    vec.resize(Poly::buffer(vec));
    vector<ll> ans = Poly::exp(vec, Poly::buffer(vec));
    for (int i = 0; i < N; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
} 