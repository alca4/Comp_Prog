struct DSU {
    static vector<int> p, sz;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n);
        sz.resize(n);
        for (int i = 1; i <= n; i++) p[i] = i, sz[i] = 1;
    }

    static int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
    static int combine(int a, int b)
    {
        a = root(a), b = root(b);
        if (a == b) return 0;

        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};