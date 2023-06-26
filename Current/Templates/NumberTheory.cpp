int sieve[1000010];
vector<int> primes;
struct NumberTheory {
    
    static void get_primes(int x) {
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i])
        {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int x) {
        vector<pii> v;
        int x = 1;
        for (int p : primes) {
            v.pb(pii(p, 0));
            while (a % p == 0) {
                v.back().SS++;
                a /= p;
            }
            if (v.back().SS == 0) v.pop_back();
            else {
                v.back().SS++;
                x *= v.back().SS;
            }
        }
    }

    static vector<int> gen_div(int x) {
        vector<pii> v = factorize(x);
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

    static ll pollard(ll a) {
        MOD = a;
        ll div = -1;
        for (int g = 2; g <= 10; g++) {
            ll x = g;
            ll y = 2;
            ll d = 1;
            
            while (d == 1) {
                x = add(mult(x, x), 1);
                y = add(mult(y, y), 1);
                y = add(mult(y, y), 1);
                d = gcd(a, abs(x - y));
            }

            if (d != a) {
                div = d;
                break;
            }
        }
        return div;
    }
};