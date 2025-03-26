extern vector<int> nbs[MAXN];

struct LCA {
    vector<int> in, out;
    vector<int> lift[32];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        depth.resize(n + 1);
        for (int i = 0; i < 32; i++) lift[i].resize(n + 1);

        out[0] = 2 * n + 1;
        if (n) tour(1, 0);
    }

    void tour(int a, int p) {
        depth[a] = depth[p] + 1;

        lift[0][a] = p;
        for (int j = 1; j < 32; j++) 
            lift[j][a] = lift[j - 1][lift[j - 1][a]];
        
        in[a] = ++T;
        for (int nb : nbs[a]) if (nb != p) tour(nb, a);
        out[a] = ++T;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    int lca(int a, int b) {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = 31; i >= 0; i--) 
            if (!is_anc(lift[i][a], b)) a = lift[i][a];
                
        return lift[0][a];
    }
};