struct LCA {
    vector<int> in, out, euler;
    vector<int> lift[32];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        euler.resize(n + 1);
        for (int i = 0; i < 32; i++) lift[i].resize(n + 1);
    }

    void tour(int a, int p)
    {
        lift[a][0] = p;
        for (int j = 1; j < 32; j++) 
            lift[a][j] = lift[lift[a][j - 1]][j - 1];
        in[a] = ++T;
        euler[T] = a;
        for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
        out[a] = ++T;
        euler[T] = -a;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    void setup_lca() {tour(/*root, itself*/);}
    int lca(int a, int b)
    {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = 31; i >= 0; i--)
            if (!is_anc(lift[a][i], b)) a = lift[a][i];
        
        return lift[a][0];
    }
};