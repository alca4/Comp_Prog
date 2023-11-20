#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v;
    int v2;
    ll sv;
    bool rev;
    int ch[2], sz;
};
struct PTreap {
    Node nodes[MAXN];
    int cap = 0;
    int op = 0;
    int rt[200010];

    PTreap() {
        rt[op++] = -1;
    }

    int copy(int n) {
        nodes[cap++] = nodes[n];
        return cap - 1;
    }

    int find(int n, int v, int before) {
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        int ret;
        if (nodes[n].lc >= 0 && v < d) ret = find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) ret = find(nodes[n].rc, v, d + 1);
        else ret = n;
        return ret;
    }

    pii split(int n, int v, int before) {
        if (n >= 0) {
            int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
            push(n);
            int nn = copy(n);
            if (v < d) {
                pii x = split(nodes[nn].lc, v, before);
                nodes[nn].lc = x.SS;
                pull(nn);
                return pii(x.FF, nn);
            }
            else {
                pii x = split(nodes[nn].rc, v, d + 1);
                nodes[nn].rc = x.FF;
                pull(nn);
                return pii(nn, x.SS);
            }
        }
        return pii(-1, -1);
    }

    int merge(int m, int n) {
        if (m == -1) return n;
        if (n == -1) return m;

        push(m);
        push(n);

        if (nodes[m].v2 > nodes[n].v2) {
            nodes[m].rc = merge(nodes[m].rc, n);
            pull(m);
            return m;
        }
        else {
            nodes[n].lc = merge(m, nodes[n].lc);
            pull(n);
            return n;
        }
    }

    void insert(int n, int idx, int v) {
        int nn = cap++;
        nodes[nn] = {v, rand(), v, 0, -1, -1, 1};
        pii x = split(n, idx - 1, 0);
        rt[op++] = merge(merge(x.FF, nn), x.SS);
    }

    void erase(int n, int idx) {
        pii x = split(n, idx - 1, 0);
        pii y = split(x.SS, 0, 0);
        rt[op++] = merge(x.FF, y.SS);
    }

    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }
        cout << n << " " << nodes[n].v << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
    }

    // updates & queries
    void apply(int n, int r) {
        nodes[n].rev ^= r;
        swap(nodes[n].lc, nodes[n].rc);
    }

    void push(int n) {
        if (!nodes[n].rev) return;
        if (nodes[n].lc >= 0) {
            nodes[n].lc = copy(nodes[n].lc);
            apply(nodes[n].lc, nodes[n].rev);
        }
        if (nodes[n].rc >= 0) {
            nodes[n].rc = copy(nodes[n].rc);
            apply(nodes[n].rc, nodes[n].rev);
        }
        nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sv = nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0);
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
    }

    void update(int n, int l, int r) {
        pii x = split(n, l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        apply(y.FF, 1);
        push(y.FF);

        rt[op++] = merge(x.FF, merge(y.FF, y.SS));
    }

    ll query(int n, int l, int r) {
        pii x = split(n, l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        push(y.FF);
        ll v = nodes[y.FF].sv;
        rt[op++] = merge(x.FF, merge(y.FF, y.SS));
        return v;
    }
};