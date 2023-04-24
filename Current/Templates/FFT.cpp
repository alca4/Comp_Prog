ll w[(1 << 17)];
void dft(vector<ll>& a, int tot, bool inv)
{
    ll g = 3;
    if (inv) g = power(g, MOD - 2);
    int sz = (1 << tot);

    for (int i = 1, j = 0; i < sz; i++) {
        int bit = sz >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int i = 0; i < tot; i++) 
    {
        w[0] = 1;
        ll t = power(g, (MOD - 1) / (1 << (i + 1)));
        for (int j = 1; j < (1 << i); j++) w[j] = (w[j - 1] * t) % MOD;
        for (int j = 0; j < sz; j += (1 << (i + 1)))
        {
            for (int k = 0; k < (1 << i); k++)
            {
                ll v = (w[k] * a[j + k + (1 << i)]) % MOD;
                ll f = (a[j + k] + v) % MOD;
                ll s = (a[j + k] + MOD - v) % MOD;
                a[j + k] = f;
                a[j + k + (1 << i)] = s;
            }
        }
    }

    if (inv)
    {
        ll szinv = power(sz, MOD - 2);
        for (int i = 0; i < sz; i++) a[i] = (a[i] * szinv) % MOD;
    }
}

vector<ll> fft(vector<ll>& a, vector<ll>& b)
{
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