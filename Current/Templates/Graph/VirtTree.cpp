extern vector<int> nbs[MAXN];

struct LCA {
    vector<int> in, out, depth;
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

struct VT{
    vector<int> key;
    vector<int> key_nodes;
    vector<vector<int>> vnbs;
    vector<int> chain;
    vector<int> extras;
    LCA lca;

    VT() {VT(0);}
    VT(int n) {
        key.resize(n + 1);
        vnbs.resize(n + 1);
        lca = LCA(n);
    }

    void setup_virtual_tree(const vector<int>& kn) {
        key_nodes = kn;
        sort(key_nodes.begin(), key_nodes.end(), [this](const int& a, const int& b) -> bool {
            return lca.in[a] < lca.in[b];
        });
    
        for (int n : key_nodes) key[n] = 1;

        vector<int> chain;
        chain.pb(key_nodes[0]);

        for (int j = 1; j < key_nodes.size(); j++) {
            int c = lca.lca(chain.back(), key_nodes[j]);

            while (chain.size() > 1 && lca.depth[c] <= lca.depth[chain[chain.size() - 2]]) {
                vnbs[chain[chain.size() - 2]].pb(chain[chain.size() - 1]);
                chain.pop_back();
            }

            if (!key[c]) {
                vnbs[c].pb(chain.back());
                chain.pop_back();
                chain.pb(c);
                extras.pb(c);
                key[c] = 2;
            }

            chain.pb(key_nodes[j]);
        }

        while (chain.size() > 1) {
            int x = chain.back();
            chain.pop_back();
            vnbs[chain.back()].pb(x);
        }
        
        for (int n : key_nodes) if (!root || lca.is_anc(n, root)) root = n;
        for (int n : extras) if (!root || lca.is_anc(n, root)) root = n;

        chain.pop_back();
    }

    void clear_virtual_tree() {
        for (int i : key_nodes) {
            vnbs[i].clear();
            key[i] = 0;
        }

        for (int i : extras) {
            vnbs[i].clear();
            key[i] = 0;
        }

        extras.clear();
        key_nodes.clear();
        while (!chain.empty()) chain.pop_back();
    }
};
