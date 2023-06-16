/*
  ___
 (o, o)
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

ll add(const ll &a, const ll &b) {
    ll x = a + b;

    if (a + b >= MOD)
        x -= MOD;

    return x;
}
ll sub(const ll &a, const ll &b) {
    ll x = a - b;

    if (a - b < 0)
        x += MOD;

    return x;
}
ll mult(const ll &a, const ll &b) {
    return (a * b) % MOD;
}
ll binexp[32];
ll power(ll a, ll b) {
    ll n = b;
    ll ans = 1;

    binexp[0] = a;

    for (int i = 1; i < 32; i++)
        binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0) {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll &a, const ll &b) {
    return (a * power(b, MOD - 2)) % MOD;
}
template<class X, class Y> void maxeq(X &x, Y y) {
    if (x < y)
        x = y;
}
template<class X, class Y> void mineq(X &x, Y y) {
    if (x > y)
        x = y;
}
template<class X, class Y> void addeq(X &x, Y y) {
    x = add(x, y);
}
template<class X, class Y> void subeq(X &x, Y y) {
    x = sub(x, y);
}
template<class X, class Y> void multeq(X &x, Y y) {
    x = mult(x, y);
}
template<class X, class Y> void diveq(X &x, Y y) {
    x = divide(x, y);
}

const int MAXN = 0;
int N;
ll w[(1 << 25)];

struct Poly {
    static void dft(vector<ll> &a, int tot, bool inv) {
        ll g = 3;

        if (inv)
            g = power(g, MOD - 2);

        int sz =  (1 << tot) ;

        for (int i = 1, j = 0; i < sz; i++) {
            int bit = sz >> 1;

            for (; j & bit; bit >>= 1)
                j ^= bit;

            j ^= bit;

            if (i < j)
                swap(a[i], a[j]);
        }

        for (int i = 0; i < tot; i++) {
            w[0] = 1;
            ll t = power(g, (MOD - 1) / (1 << (i + 1)));

            for (int j = 1; j < (1 << i); j++)
                w[j] = (w[j - 1] * t) % MOD;

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

            for (int i = 0; i < sz; i++)
                a[i] = (a[i] * szinv) % MOD;
        }
    }

    static vector<ll> slowmult(vector<ll> &a, vector<ll> &b) {
        vector<ll> c(a.size() + b.size() - 1);

        for (int i = 0; i < a.size(); i++)
            for (int j = 0; j < b.size(); j++) {
                c[i + j] += a[i] * b[j];
                c[i + j] %= MOD ; 
            }

        return c;
    }

    static vector<ll> pmult(vector<ll> a, vector<ll> b) {
        // if (min(a.size(), b.size()) < 100) return slowmult(a, b);
        int tot = 32 - __builtin_clz(a.size() + b.size() - 1);
        if (a.size() == 1 && b.size() == 1) tot = 0;

        int sz =  (1 << tot) ;

        a.resize(sz);
        b.resize(sz);

        dft (a, tot, 0) ; 
        dft (b, tot, 0) ;

        vector<ll> c(sz);

        for (int i = 0; i < sz; i++)
            c[i] = (a[i] * b[i]) % MOD;

        dft(c, tot, 1);
        c.resize(a.size() + b.size() - 1);
        return c;
    }

    static vector<ll> invert(vector<ll> &f) {
        vector<ll> g;
        g.pb(power(f[0], MOD - 2));

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> t3;
            for (int j = 0; j < min((int) f.size(), i); j++) t3.pb(f[j]);
            vector<ll> t2 = pmult(g, g);
            t2.resize(min((int) t2.size(), i));
            t2 = pmult(t2, t3);
            g.resize(i);

            for (int j = 0; j < i; j++) {
                g[j] += g[j];
                if (t2.size() > j) g[j] += MOD - t2[j];
                g[j] %= MOD ; 
            } 
        }

        return g;
    }

    static vector<ll> sqrt(vector<ll> &f) {
        ll m = 23;
        ll c = power(3, 119);
        ll t = power(f[0], 119);
        ll r = power(f[0], 60);

        ll v = -1;

        while (v < 0) {
            if (t == 0)
                v = 0;

            if (t == 1)
                v = r;

            int i = 1;

            for (; i < m; i++)
                if (power(t, power(2, i)) == 1)
                    break;

            ll b = power(c, power(2, m - i - 1));

            m = i;
            c = power(b, 2);
            t = mult(t, c);
            r = mult(r, b);
        }

        vector<ll> g;

        if (MOD - v < v)
            v = MOD - v;

        g.pb(v);

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> t2;
            for (int j = 0; j < min((int) f.size(), i); j++) t2.pb(f[j]);
            g.resize(i);
            vector<ll> t1 = invert(g);
            t1 = pmult(t2, t1);

            for (int j = 0; j < i; j++) {
                g[j] = (g[j] + t1[j]) * (MOD + 1) / 2;
                g[j] %= MOD;
            }
        }

        return g;
    }

    static void integral(vector<ll> &f) {
        f.resize(f.size() + 1);

        for (int i = f.size() - 2; i >= 0; i--) {
            f[i + 1] = divide(f[i], i + 1);
            f[i] = 0;
        }
    }

    static void derivative(vector<ll> &f) {
        f[0] = 0;

        for (int i = 1; i < f.size(); i++) {
            f[i - 1] = f[i] * i;
            f[i - 1] %= MOD;
            f[i] = 0;
        }
    }

    static vector<ll> exp(vector<ll> &f) {
        vector<ll> g;
        g.pb(1);

        for (int i = 2; i <= buffer(f); i <<= 1) {
            vector<ll> tg = g;
            tg.resize(i);
            tg = ln(g);

            vector<ll> h(i / 2);
            h[0] = 1;

            for (int j = 0; j < i / 2; j++) {
                if (f.size() > j)
                    h[j] += f[j];

                if (tg.size() > j)
                    h[j] += MOD - tg[j];

                h [ j ]  %= MOD ; 
            }

            h.resize(i / 2);
            g.resize(i / 2);
            g = pmult(h, g);
            g.resize(i);
        }

        return g;
    }

    static vector<ll> ln(vector<ll> &f) {
        vector<ll> tmp = f;
        vector<ll> ans = invert(f);
        ans.resize(f.size());
        derivative(tmp);
        ans = pmult(tmp, ans);
        ans.resize(f.size());
        integral(ans);
        ans.resize(f.size());
        return ans;
    }

    static vector<ll> ppower(vector<ll> &f, int k) {
        vector<ll> ans = ln(f);

        for (int i = 0; i < f.size(); i++) {
            ans[i] *= k;
            ans[i] %= MOD;
        }

        ans = exp(ans);
        ans.resize(f.size());
        return ans;
    }

    static int buffer(vector<ll> &f) {
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

    int K;
    cin >> N >> K;
    N++;
    vector<ll> vec;

    for (int i = 0; i < N; i++) {
        int n;
        cin >> n;
        vec.pb(n);
    }

    auto start = clock();
    vector<ll> ans = Poly::sqrt(vec);
    // cerr << "sqrt" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    ans = Poly::invert(ans);
    // cerr << "inv" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    Poly::integral(ans);
    // cerr << "int" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    ans = Poly::exp(ans);
    // cerr << "exp" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    int init = ans[0];

    for (int i = 0; i < N + 1; i++) {
        ans[i] = vec[i] + MOD - ans[i];
        ans[i] %= MOD;
    }

    ans[0] = ans[0] - vec[0] + 2;
    ans = Poly::ln(ans);
    // cerr << "ln" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    ans[0]++;
    ans = Poly::ppower(ans, K);
    // cerr << "power" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    // start = clock();
    Poly::derivative(ans);

    // cerr << "der" << endl;
    // cerr << (float) (clock() - start) / CLOCKS_PER_SEC << endl;
    for (int i = 0; i < N - 1; i++)
        cout << ans[i] << " ";

    cout << endl;
    return 0;
}