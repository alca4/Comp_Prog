struct ST {
    vector<ll> seg, lazy, lc, rc;

    PST() {
        create();
    }

    int create() {
        seg.pb(0);
        lazy.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return seg.size() - 1;
    }

    void apply(ll v, int cid) {
        lazy[cid] += v;
        seg[cid] += v;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            if (lc[cid] == -1) lc[cid] = create();
            apply(lazy[cid], lc[cid]);
            if (rc[cid] == -1) rc[cid] = create();
            apply(lazy[cid], rc[cid]);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a <= ss && se <= b) {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) {
            if (lc[cid] == -1) lc[cid] = create();
            update(a, v, lc[cid], ss, mid);
        }
        else {
            if (rc[cid] == -1) rc[cid] = create();
            update(a, v, rc[cid], mid + 1, se);
        }

        seg[cid] = 0;
        if (lc[cid] != -1) seg[cid] += seg[lc[cid]];
        if (rc[cid] != -1) seg[cid] += seg[rc[cid]];
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid && lc[cid] != -1) {
            ans += query(a, b, lc[cid], ss, mid);
        }
        if (b > mid && rc[cid] != -1) {
            ans += query(a, b, rc[cid], mid + 1, se);
        }

        return ans;
    }

    void clear() {
        seg.clear();
        lazy.clear();
        lc.clear();
        rc.clear();
    }
};