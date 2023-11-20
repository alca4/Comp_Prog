#define lc ch[0]
#define rc ch[1]

struct Node {
    int v, p, ch[2], sz;
};

struct SplayTree {
    vector<Node> nodes;
    int rt;

    SplayTree() {
        rt = -1;
    }

    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }

    void rotate(int n) {
        int p = nodes[n].p;
        int dn = dir(n);
        int dp = dir(p);
        int tsz = (nodes[n].ch[dn] >= 0 ? nodes[nodes[n].ch[dn]].sz : 0);
        nodes[p].ch[dn] = nodes[n].ch[dn ^ 1];
        nodes[nodes[n].ch[dn ^ 1]].p = p;

        nodes[n].p = nodes[p].p;
        if (dp >= 0) 
            nodes[nodes[p].p].ch[dp] = n;
            
        nodes[n].ch[dn ^ 1] = p;
        nodes[p].p = n;

        nodes[n].sz = nodes[p].sz;
        nodes[p].sz -= tsz + 1;
    }

    int splay(int n) {
        rt = n;
        while (dir(n) >= 0) {
            int p = nodes[n].p;
            int dn = dir(n);
            int dp = dir(p);

            if (dp >= 0)
                rotate(dn == dp ? p : n);

            rotate(n);
        }

        return n;
    }

    int find(int n, int v, int before) {
        if (nodes[n].lc >= 0 && v < before + nodes[nodes[n].lc].sz + 1) 
            return find(nodes[n].lc, v, before + nodes[nodes[n].lc].sz + 1);

        else if (nodes[n].rc >= 0 && before + nodes[nodes[n].lc].sz + 1 < v) 
            return find(nodes[n].rc, v, before + nodes[nodes[n].lc].sz + 1); 
        
        else 
            return splay(n);
    }

    pii split(int n, int v) {
        n = find(n, v, 0);

        int x = nodes[n].v <= v;
        if (nodes[n].ch[x] == -1) 
            return pii(n, -1);
            
        int n2 = nodes[n].ch[x];
        nodes[n2].p = -1;
        nodes[n].ch[x] = -1;
        nodes[n].sz -= nodes[n2].sz;
        if (!x) swap(n, n2);
        return pii(n, n2);
    }

    // all elements in m should be less than elements in n
    int merge(int m, int n) {
        if (m == -1) 
            return rt = n;
        
        if (n == -1)
            return rt = m;

        if (nodes[m].v > nodes[n].v) 
            swap(m, n);

        m = find(m, INF, 0);

        nodes[m].rc = n;
        nodes[n].p = m;
        nodes[m].sz += nodes[n].sz;

        return m;
    }

    int insert(int n, int v) {
        if (nodes.empty()) {
            nodes.pb({v, -1, -1, -1, 1});
            return rt = 0;
        }
        
        pii x = split(n, v);

        nodes.pb({v, -1, -1, -1, 1});

        x.FF = merge(x.FF, nodes.size() - 1);
        x.FF = merge(x.FF, x.SS);

        return x.FF;
    }

    int erase(int n, int v) {
        n = find(n, v, 0);

        pii x = split(n, v - 1);
        pii y = split(x.SS, v);
        return merge(x.FF, y.SS);
    }

    void print(int n) {
        if (n == -1) {
            cout << "-1" << endl;
            return;
        }
        cout << n << " " << nodes[n].v << " " << nodes[n].lc << " " << nodes[n].rc << endl;

        if (nodes[n].lc >= 0)
            print(nodes[n].lc);

        if (nodes[n].rc >= 0)
            print(nodes[n].rc);
    }
};

int main() {
    SplayTree st;
    st.insert(st.rt, 1);
    st.insert(st.rt, 3);
    st.insert(st.rt, 2);
    // st.insert(st.rt, 4);
    // st.find(st.rt, 2, 0);

    st.print(st.rt);
    cout << endl;

    return 0;
}