ll w[(1 << 25)];
struct Poly {
    static void dft(vector<ll> &a, int tot, bool inv) {
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