struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;
        ll lazy = 0;

        void merge(Node& b, Node& c) {
            sum = b.sum + c.sum;
            minv = min(b.minv, c.minv);
            maxv = max(b.maxv, c.maxv);
        }
    };
    vector<Node> seg;

    ST(int n) {
        seg.resize(n * 4 + 1);
    }

    void apply(int cid, ll v, int ss, int se) {
        seg[cid].lazy += v;
        seg[cid].sum += v * (se - ss + 1);
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void push(int cid, int ss, int se) {
        if (seg[cid].lazy && ss != se) {
            int mid = (ss + se) / 2;
            apply(cid * 2, seg[cid].lazy, ss, mid);
            apply(cid * 2 + 1, seg[cid].lazy, mid + 1, se);
        }
        seg[cid].lazy = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            apply(cid, v, ss, se);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF, 0};
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            ans.merge(ans, rans);
        }
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = Node();
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};