struct PST {
    vector<ll> seg, lc, rc;
    vector<int> roots;

    PST() {
        create();
        roots.pb(0);
    }

    int create() {
        seg.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return seg.size() - 1;
    }

    int update(int a, ll v, int cid, int ss, int se) {
        int nn = create();
        lc[nn] = lc[cid];
        rc[nn] = rc[cid];
        seg[nn] = seg[cid];
        if (ss == se) {
            seg[nn] += v;
            return nn;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) {
            if (lc[nn] == -1) lc[nn] = create();
            lc[nn] = update(a, v, lc[nn], ss, mid);
        }
        else {
            if (rc[nn] == -1) rc[nn] = create();
            rc[nn] = update(a, v, rc[nn], mid + 1, se);
        }

        seg[nn] = 0;
        if (lc[nn] != -1) seg[nn] += seg[lc[nn]];
        if (rc[nn] != -1) seg[nn] += seg[rc[nn]];
        return nn;
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

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

    void clear(int cid, int ss, int se) {
        seg[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};