#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sum, m, x, set, add;
    int p, pp, rev, ch[2], sz;
};
struct LCT {
    Node nodes[MAXN];
    int cap = 0;

    void DFS(int a, int p) {
        for (int nb : nbs[a]) if (nb != p) {
            DFS(nb, a);
            nodes[nb - 1].pp = a - 1;
        }
    }

    void build(int rt) {
        for (int i = 1; i <= N; i++) 
            insert(arr[i]);
        DFS(rt, -1);
    }
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }

    void con(int m, int n, int dir) {
        push(m);
        // cout << "edge created between " << m << " and " << n << endl;
        nodes[m].ch[dir] = n;
        nodes[n].p = m;
        nodes[n].pp = -1;
        pull(m);
    }

    void dc(int n, int dir) {
        push(n);
        int n2 = nodes[n].ch[dir];
        if (n2 >= 0) {
            // cout << "edge destroyed between " << n << " and " << n2 << endl;
            nodes[n2].p = -1;
            nodes[n2].pp = n;
            nodes[n].ch[dir] = -1;
        }
        pull(n);
    }
 
    void rotate(int n) {
        int p = nodes[n].p;
        int dn = dir(n);
        int dp = dir(p);
        push(p);
        push(n);
        int opp = nodes[n].ch[dn ^ 1];
        
        nodes[p].ch[dn] = opp;
        if (opp >= 0) nodes[opp].p = p;
 
        nodes[n].p = nodes[p].p;
        nodes[n].pp = nodes[p].pp;
        if (nodes[p].p >= 0) nodes[nodes[p].p].ch[dp] = n;
            
        nodes[n].ch[dn ^ 1] = p;
        nodes[p].p = n;
        nodes[p].pp = -1;
        pull(p);
        pull(n);
    }
 
    int splay(int n) {
        while (dir(n) >= 0) {
            int p = nodes[n].p;
            int dn = dir(n);
            int dp = dir(p);
 
            if (dp >= 0) rotate(dn == dp ? p : n);
            rotate(n);
        }
 
        return n;
    }
 
    void insert(int v) {
        nodes[cap++] = {v, v, v, v, LINF, 0, -1, -1, 0, -1, -1, 1};
    }
 
    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }

        push(n);
        cout << n << " " << nodes[n].m << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
        pull(n);
    }

    void apply(int n, ll s, ll a, int r) {
        if (r) {
            nodes[n].rev ^= r;
            swap(nodes[n].lc, nodes[n].rc);
        }
        if (s != LINF) {
            nodes[n].set = s;
            nodes[n].add = 0;

            nodes[n].sum = s * nodes[n].sz;
            nodes[n].m = nodes[n].x = s;
            nodes[n].v = s;
        }
        if (a != 0) {
            nodes[n].add += a;

            nodes[n].sum += a * nodes[n].sz;
            nodes[n].m += a;
            nodes[n].x += a;
            nodes[n].v += a;
        }
    }

    void push(int n) {
        if (nodes[n].set == LINF && nodes[n].add == 0 && nodes[n].rev == 0) return;
        if (nodes[n].lc >= 0) apply(nodes[n].lc, nodes[n].set, nodes[n].add, nodes[n].rev);
        if (nodes[n].rc >= 0) apply(nodes[n].rc, nodes[n].set, nodes[n].add, nodes[n].rev);
        nodes[n].set = LINF;
        nodes[n].add = nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
        nodes[n].sum = nodes[n].v +
                       (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sum : 0) +
                       (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sum : 0);
        nodes[n].m = min({nodes[n].v, 
                         (nodes[n].lc >= 0 ? nodes[nodes[n].lc].m : LINF), 
                         (nodes[n].rc >= 0 ? nodes[nodes[n].rc].m : LINF)});
        nodes[n].x = max({nodes[n].v, 
                         (nodes[n].lc >= 0 ? nodes[nodes[n].lc].x : -LINF), 
                         (nodes[n].rc >= 0 ? nodes[nodes[n].rc].x : -LINF)});
    }

    // lct methods
    int access(int n) {
        int tn = n;
        splay(n);
        dc(n, 1);
        while (nodes[n].pp != -1) {
            int p = nodes[n].pp;
            // cout << "meeting " << p << endl;
            splay(p);
            if (nodes[p].rc >= 0) dc(p, 1);
            con(p, n, 1);
            n = p;
        }
        splay(tn);
        return n;
    }

    int root(int n) {
        access(n);
        while (nodes[n].lc >= 0) n = nodes[n].lc;
        splay(n);
        return n;
    }

    void reroot(int n) { 
        access(n);
        apply(n, LINF, 0, 1);
    }

    void link(int m, int n) {
        reroot(m);
        nodes[m].pp = n;
    }

    void cut(int m, int n) {
        reroot(m);
        access(n);
        push(n);
        // cout << "edge destroyed between " << n << " and " << m << endl;
        nodes[n].lc = -1;
        nodes[m].p = -1;
        nodes[m].pp = -1;
        pull(n);
    }

    void update(int m, int n, int t, ll a) {
        reroot(m);
        access(n);

        if (t == 1) apply(n, a, 0, 0);
        if (t == 2) apply(n, LINF, a, 0);

        push(n);
    }

    ll query(int m, int n, int t) {
        reroot(m);
        access(n);

        push(n);
        ll ret;
        if (t == 3) ret = nodes[n].m;
        if (t == 4) ret = nodes[n].x;
        if (t == 5) ret = nodes[n].sum;
        return ret;
    }

    int lca(int m, int n) {
        access(m);
        int ret = access(n);
        return ret;
    }
};