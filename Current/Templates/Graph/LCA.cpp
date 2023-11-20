struct LCA {
    vector<int> in, out;
    vector<int> lift[32];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        for (int i = 0; i < 32; i++) lift[i].resize(n + 1);
        in[0] = 0;
        out[0] = INF;
        setup_lca();
    }

    void tour(int a, int p) {
        lift[0][a] = p;
        for (int j = 1; j < 32; j++) 
            lift[j][a] = lift[j - 1][lift[j - 1][a]];
        in[a] = ++T;
        for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
        out[a] = ++T;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    void setup_lca() {tour(1, 0);}
    int lca(int a, int b) {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = 31; i >= 0; i--) 
            if (!is_anc(lift[i][a], b)) a = lift[i][a];
        
        return lift[0][a];
    }

    int dist(int a, int b) {
        if (a == b) return 0;
        if (is_anc(a, b)) swap(a, b);

        int t = a;
        int d = 0;
        for (int i = 31; i >= 0; i--)
            if (!is_anc(lift[i][t], b)) {
                t = lift[i][t];
                d += (1 << i);
            }
        
        return d + 1;
    }

    int travel(int a, int dist) {
        for (int i = 31; i >= 0; i--) {
            if (dist & (1 << i)) a = lift[i][a];
        }
        return a;
    }
};