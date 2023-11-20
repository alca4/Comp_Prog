vector<cd> dft(vector<cd>& a, int tot, int inv) {
    vector<cd> a2(N);
    for (int i = 0; i < N; i++) {
        int tmp = i;
        int l = 1, r = N;
 
        for (int j = 0; j <= tot; j++) {
            int mid = (l + r) / 2;
            if (tmp & 1) l = mid + 1;
            else r = mid;
            tmp >>= 1;
        }
 
        a2[l - 1] = a[i];
    }
 
    for (int i = 1; i < N; i <<= 1) {
        cd t = cd(cos(2.0 * inv * acos(-1) / (i * 2)),
                  sin(2.0 * inv * acos(-1) / (i * 2)));
        for (int j = 0; j < N; j += i * 2) {
            cd w = 1;
            for (int k = 0; k < i; k++) {
                cd f = a2[j + k] + w * a2[j + k + i];
                cd s = a2[j + k] - w * a2[j + k + i];
                a2[j + k] = f;
                a2[j + k + i] = s;
                w *= t;
            }
        }
    }
    
    if (inv == -1) {
        for (int i = 0; i < N; i++) a2[i] /= N;
    }
 
    return a2;
}

vector<ll> fft(vector<ll> a, vector<ll> b) {
    int tot = 32 - __builtin_clz(a.size() + b.size() - 1);
    if (a.size() == 1 && b.size() == 1) tot = 0;
    int sz = (1 << tot);

    dft(a, sz, 1);
    dft(b, sz, 1);

    for (int i = 0; i < sz; i++) a[i] *= b[i];

    return dft(a, sz, -1);
}