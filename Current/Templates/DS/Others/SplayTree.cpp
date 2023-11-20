#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sv, lm, la;
    bool rev;
    int p, ch[2], sz;
};
struct SplayTree {
    Node nodes[MAXN];
    int cap = 0;
    int rt;
 
    SplayTree() {insert(0, 0, 0);}
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }
 
    void rotate(int n) {
        int p = nodes[n].p;
        push(p);
        push(n);
        int dn = dir(n);
        int dp = dir(p);
        int same = nodes[n].ch[dn];
        int opp = nodes[n].ch[dn ^ 1];
        
        int tsz = (same >= 0 ? nodes[same].sz : 0);
        nodes[p].ch[dn] = opp;
        if (opp >= 0) nodes[opp].p = p;
 
        nodes[n].p = nodes[p].p;
        if (nodes[p].p >= 0) nodes[nodes[p].p].ch[dp] = n;
            
        nodes[n].ch[dn ^ 1] = p;
        nodes[p].p = n;
 
        nodes[n].sz = nodes[p].sz;
        nodes[p].sz -= tsz + 1;
 
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
 
        return rt = n;
    }
 
    int find(int n, int v, int before) {
        push(n);
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        int ret;
        if (nodes[n].lc >= 0 && v < d) ret = find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) ret = find(nodes[n].rc, v, d + 1);
        else ret = splay(n);
        pull(n);
        return ret;
    }
 
    pii split(int n, int v) {
        if (n < 0) return pii(-1, -1);
        n = find(n, v, 0);
        int n2 = nodes[n].rc;
        if (n2 == -1) return pii(n, -1);
        
        push(n);
        nodes[n2].p = -1;
        nodes[n].rc = -1;
 
        nodes[n].sz -= nodes[n2].sz;
        pull(n);
        return pii(n, n2);
    }
 
    int merge(int m, int n) {
        if (m == -1) return n;
        if (n == -1) return m;
 
        n = find(n, 0, 0);

        push(n);
        nodes[n].lc = m;
        nodes[m].p = n;
        nodes[n].sz += nodes[m].sz;
        pull(n);
        return n;
    }
 
    void insert(int n, int idx, int v) {
        nodes[cap++] = {v, v, 1, 0, 0, -1, -1, -1, 1};
        if (cap == 1) return;

        pii x = split(n, idx - 1);

        rt = merge(merge(x.FF, cap - 1), merge(rt, x.SS));
    }

    void erase(int n, int idx) {
        pii x = split(n, idx - 1);
        pii y = split(x.SS, 0);
        rt = merge(x.FF, y.SS);
    }
 
    // updates and queries
    void apply(int n, int b, int c, bool r) {
        nodes[n].la = (nodes[n].la * b + c) % MOD;
        nodes[n].lm = (nodes[n].lm * b) % MOD;
        nodes[n].v = (nodes[n].v * b + c) % MOD;
        nodes[n].sv = (nodes[n].sv * b + 1ll * c * nodes[n].sz) % MOD;
        nodes[n].rev ^= r;
        if (r) swap(nodes[n].lc, nodes[n].rc);
    }

    void push(int n) {
        if (nodes[n].lm == 1 && nodes[n].la == 0 && nodes[n].rev == 0) return;
        
        if (nodes[n].lc >= 0) 
            apply(nodes[n].lc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        if (nodes[n].rc >= 0) 
            apply(nodes[n].rc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        nodes[n].la = nodes[n].rev = 0;
        nodes[n].lm = 1;
    }

    void pull(int n) {
        nodes[n].sv = (nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0)) % MOD;
    }

    void update(int n, int l, int r, int a, int b) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        apply(y.FF, a, b, 0);
        push(y.FF);

        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
    }

    void reverse(int n, int l, int r) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        apply(y.FF, 1, 0, 1);
        push(y.FF);

        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
    }
 
    ll query(int n, int l, int r) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        push(y.FF);
        ll v = nodes[y.FF].sv;
 
        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
        return v;
    }
 
    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }
        push(n);
        cout << n << " " << nodes[n].sv << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
        pull(n);
    }
};