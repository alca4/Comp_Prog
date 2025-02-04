struct ST {
    struct Node {
        ll sum = 0;
        ll minv = 0;
        ll maxv = 0;

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

    void addToNode(int cid, ll v) {
        seg[cid].sum += v;
        seg[cid].minv += v;
        seg[cid].maxv += v;
    }

    void setNode(int cid, ll v) {
        seg[cid].sum = v;
        seg[cid].minv = v;
        seg[cid].maxv = v;
    }

    void set(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            setNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void update(int a, ll v, int cid, int ss, int se) {
        if (ss == se) {
            addToNode(cid, v);
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].merge(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se) {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        Node ans = {0, LINF, -LINF};
        if (a <= mid) {
            Node lans = query(a, b, cid * 2, ss, mid);
            ans.merge(ans, lans);
        }
        if (b > mid) {
            Node rans = query(a, b, cid * 2 + 1, mid + 1, se);
            ans.merge(ans, rans);
        }
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
