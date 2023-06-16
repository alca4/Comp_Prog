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
    static void padd(vector<ll>& a, vector<ll>& b) {
        int sz = max(a.size(), b.size());
        while (a.size() < sz) a.pb(0);
        while (b.size() < sz) b.pb(0);
        for (int i = 0; i < sz; i++) {
            a[i] = add(a[i], b[i]);
        }
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

        while (a.size() < sz) a.pb(0);
        while (b.size() < sz) b.pb(0);

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
        t1.resize(n);
        for (int i = 0; i < t1.size(); i++) {
            t1[i] *= 2;
            if (t1[i] >= MOD) t1[i] -= MOD;
        }
        vector<ll> t2 = g;
        vector<ll> t3 = f;
        t2.resize(n);
        t3.resize(n);
        t2 = pmult(t2, t2);
        t2.resize(n);
        t2 = pmult(t2, t3);
        t2.resize(n);
        g.resize(n);
        for (int i = 0; i < n; i++) {
            g[i] = MOD + t1[i] - t2[i];
            if (g[i] >= MOD) g[i] -= MOD;
        }
        // cerr << n << endl;
        return g;
    }

    static void sqrt(vector<ll>& f, vector<ll>& g, int n) {
        if (n == 1) {
            ll m = 23;
            ll c = power(3, 119);
            ll t = power(f[0], 119);
            ll r = power(f[0], 60);
        
            ll v = -1;
            while (v < 0) {
                if (t == 0) v = 0;
                if (t == 1) v = r;

                int i = 1;
                for (; i < m; i++) 
                    if (power(t, power(2, i)) == 1) break;
                ll b = power(c, power(2, m - i - 1));

                m = i;
                c = power(b, 2);
                t = mult(t, c);
                r = mult(r, b);
            }

            if (MOD - v < v) v = MOD - v;
            g.pb(v);
            return;
        }

        sqrt(f, g, n / 2);

        g.resize(n);

        vector<ll> h;
        // invert(g, h, n);

        vector<ll> tf = f;
        vector<ll> tg = g;
        vector<ll> th = h;

        tf.resize(n);
        tg.resize(n);
        th.resize(n);

        vector<ll> t1 = pmult(tf, th);
        t1.resize(n);
        for (int i = 0; i < n; i++) g[i] = divide(add(t1[i], tg[i]), 2);
    }

    static void integral(vector<ll>& f) {
        f.resize(f.size() + 1);
        for (int i = f.size() - 1; i >= 0; i--) {
            f[i + 1] = divide(f[i], i + 1);
            f[i] = 0;
        }
    }
    
    static void derivative(vector<ll>& f) {
        for (int i = 1; i < f.size(); i++) {
            f[i - 1] = mult(i, f[i]);
            f[i] = 0;
        }
    }

    // static void exp(vector<ll>& f) {
    //     vector<ll> g;
    //     ll fact = 1;
    //     for (int i = 0; i < f.size(); i++) {
    //         g.pb(fact);
    //         diveq(fact, i + 1);
    //     }
    //     f = pmult(f, g);
    // }

    static void ppower(vector<ll>& f, int k) {
        int sz = f.size();

        vector<ll> binexp[32];
        binexp[0] = f;
        for (int i = 1; i < 32; i++) {
            binexp[i] = pmult(binexp[i - 1], binexp[i - 1]);
            binexp[i].resize(2 * sz);
        }

        f.clear();
        f.pb(1);
        while (k > 0) {
            int id = __builtin_ctz(k & -k);
            f = pmult(f, binexp[id]);
            f.resize(2 * sz);
            k -= (k & -k);
        }
        f.resize(sz);
    }

    static void ln(vector<ll>& f) {
        int tot = 32 - __builtin_clz(f.size() - 1);
        vector<ll> g;
        // invert(f, g, (1 << tot));

        for (int i = 0; i < f.size(); i++) f[i] = sub(MOD, f[i]);
        addeq(f[0], 1);
    }

    static int buffer(vector<ll>& f) {
        int ret = (1 << (32 - __builtin_clz(f.size() - 1)));
        f.resize(ret);
        return ret;
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

    vector<ll> ans;
    Poly::buffer(vec);
    ans = Poly::invert(vec, Poly::buffer(vec));
    // cerr << ans.size() << endl;
    for (int i = 0; i < N; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
} 