// virtual tree
vector<int> key_nodes;
int key[MAXN];
vector<int> nbs2[MAXN];
stack<int> peoples;
vector<int> extras;

bool Comp(int a, int b) {
    return in[a] < in[b];
}

void setup_virtual_tree() {
    sort(key_nodes.begin(), key_nodes.end(), Comp);
    for (int n : key_nodes) key[n] = 1;

    peoples.push(key_nodes[0]);

    for (int j = 1; j < key_nodes.size(); j++) {
        int c = lca(peoples.top(), key_nodes[j]);

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