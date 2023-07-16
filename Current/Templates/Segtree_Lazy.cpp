struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

    void apply(ll v, int cid) {
        lazy[cid] += v;
        seg[cid] += v;
    }

    void push(int cid, int ss, int se) {
        if (ss != se) {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se) {
        if (a > b) return;
        if (a <= ss && se <= b) {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};