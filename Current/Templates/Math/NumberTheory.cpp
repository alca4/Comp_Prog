vector<int> primes;
vector<int> sieve;
struct NT {
    static void get_primes(int x) {
        sieve.resize(x + 1);
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int n) {
        vector<pii> v;
        for (int p : primes) {
            if (p > n) break;
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
        vector<int> divs;
        for (int i = 0; i < num_div(n); i++) {
            int t = i;
            int d = 1;
            for (pii p : v) {
                if (t % p.SS) d *= power(p.FF, t % p.SS);
                t /= p.SS;
            }
            divs.pb(d);
        }
        sort(divs.begin(), divs.end());
        return divs;
    }

    static int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power(sub(mult(a, a), n), (MOD - 1) / 2) == MOD - 1) break;
        }

        pll m = pll(a, 1);
        pll ans = pll(1, 0);

        int b = (MOD + 1) / 2;

        for (int i = 0; i < 32; i++) {
            if (b & 1) {
                ans = pll(add(mult(ans.FF, m.FF), mult(mult(ans.SS, m.SS), sub(mult(a, a), n))),
                        add(mult(ans.FF, m.SS), mult(ans.SS, m.FF)));
            }
            m = pll(add(mult(m.FF, m.FF), mult(mult(m.SS, m.SS), sub(mult(a, a), n))),
                    add(mult(m.FF, m.SS), mult(m.SS, m.FF)));
            b >>= 1;
        }

        return (ans.FF + MOD) % MOD;
    }
};