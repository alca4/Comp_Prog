// virtual tree

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

struct VirtTree{
    vector<int> key_nodes;
    vector<int> key;
    vector<vector<int>> nbs2;
    stack<int> peoples;
    vector<int> extras;
    LCA lca;

    VirtTree() {VirtTree(0);}
    VirtTree(int n) {
        key.resize(n + 1);
        nbs2.resize(n + 1);
        LCA(n);
    }

    bool Comp(int a, int b) {
        return lca.in[a] < lca.in[b];
    }

    void setup_virtual_tree() {
        sort(key_nodes.begin(), key_nodes.end(), Comp);
        for (int n : key_nodes) key[n] = 1;

        peoples.push(key_nodes[0]);

        for (int j = 1; j < key_nodes.size(); j++) {
            int c = lca.lca(peoples.top(), key_nodes[j]);

            if (c == peoples.top()) {
                peoples.push(key_nodes[j]);
                continue;
            }

            vector<int> tmp;

            while (peoples.size() && depth[c] < depth[peoples.top()]) {
                tmp.pb(peoples.top());
                peoples.pop();
            }

            tmp.pb(c);

            for (int j = 1; j < tmp.size(); j++) {
                nbs2[tmp[j]].pb(tmp[j - 1]);
            }

            if (!key[c]) {
                peoples.push(c);
                extras.pb(c);
                key[c] = 1;
            }

            peoples.push(key_nodes[j]);
        }

        while (peoples.size() > 1) {
            int x = peoples.top();
            peoples.pop();
            nbs2[peoples.top()].pb(x);
        }
    }

    void clear_virtual_tree() {
        for (int i : key_nodes) {
            nbs2[i].clear();
            key[i] = 0;
        }

        for (int i : extras) {
            nbs2[i].clear();
            key[i] = 0;
        }

        extras.clear();
        key_nodes.clear();
        while (!peoples.empty())
            peoples.pop();
    }
};