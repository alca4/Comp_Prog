struct NT {
    vector<int> primes;
    vector<int> sieve;
    vector<vector<int>> divisors;
    vector<vector<pii>> factorization;

    NT(int x) {
        sieve.resize(x + 1);
        divisors.resize(x + 1);

        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = i;
        }

        for (int i = 2; i <= x; i++) {
            if (!sieve[i]) {
                divisors[i].pb(1);
                divisors[i].pb(i);
            }
            else {
                divisors[i] = divisors[i / sieve[i]];
                for (int n : divisors[i / sieve[i]]) if ((i / sieve[i] / n) % sieve[i]) {
                    divisors[i].pb(n * sieve[i]);
                }
            }
        }

        for (int i = 2; i <= x; i++) {
            if (!sieve[i]) factorization[i].pb(pii(i, 1));
            else {
                factorization[i] = factorization[i / sieve[i]];
                for (int j = 0; j < factorization[i / sieve[i]].size(); j++) {
                    if (factorization[i / sieve[i]][j].FF == sieve[i]) 
                        factorization[i / sieve[i]][j].SS++;
                }
            }
        }
    }

    int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power((a * a - n) % MOD, (MOD - 1) / 2) == MOD - 1) break;
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