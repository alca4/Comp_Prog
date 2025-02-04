struct KRT {
    int sz;
    vector<int> p;
    vector<pii> nbs[2];

    KRT() {KRT(0);}
    KRT(int n) {
        sz = n;
        nbs[0].reserve(2 * sz);
        nbs[1].reserve(2 * sz);
        p.reserve(2 * sz);

        nbs[0].resize(sz + 1);
        nbs[1].resize(sz + 1);
        p.resize(sz + 1);
        for (int i = 1; i <= sz; i++) p[i] = i;
    }

    int root(int a) {
        if (a == p[a]) return a;
        return p[a] = root(p[a]);
    }

    int combine(int a, int b, int c) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        sz++;
        p.pb(sz);
        p[a] = p[b] = sz;

        nbs[0].pb(pii(a, c));
        nbs[1].pb(pii(b, c));
        return 1;
    }
};