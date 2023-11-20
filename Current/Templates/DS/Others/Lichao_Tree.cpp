struct Line {
    ll m, b;

    ll valueAt(int x) {
        return m * x + b;
    }

    ld intersect(const Line& other) {
        return 1.0 * (other.b - b) / (m - other.m);
    }
};

struct Node {
    Line l;
    int lc = -1, rc = -1;
};

struct LichaoTree {
    vector<Node> seg;

    LichaoTree() {
        create({0, 0});
    }

    int create(Line l) {
        seg.pb({l, -1, -1});
        return seg.size() - 1;
    }

    void insert(Line l, int cid, int ss, int se) {
        int mid = (ss + se) / 2;

        bool dl = l.valueAt(ss) > seg[cid].l.valueAt(ss);
        bool dm = l.valueAt(mid) > seg[cid].l.valueAt(mid);

        if (dm) {
            Line temp = l;
            l = seg[cid].l;
            seg[cid].l = temp;
        }

        if (ss == se) return;
        else if (dl != dm) {
            if (seg[cid].lc == -1) seg[cid].lc = create({0, 0});
            insert(l, seg[cid].lc, ss, mid);
        }
        else {
            if (seg[cid].rc == -1) seg[cid].rc = create({0, 0});
            insert(l, seg[cid].rc, mid + 1, se);
        }
    }

    ll query(int a, int cid, int ss, int se) {
        ll ans = seg[cid].l.valueAt(a);
        if (ss == se) return ans;

        ll mid = (ss + se) / 2;
        if (a <= mid && seg[cid].lc >= 0) ans = max(ans, query(a, seg[cid].lc, ss, mid));
        else if (seg[cid].rc >= 0) ans = max(ans, query(a, seg[cid].rc, mid + 1, se));
        return ans;
    }
};