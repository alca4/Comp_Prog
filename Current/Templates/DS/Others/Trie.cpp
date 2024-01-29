struct Trie {
    vector<int> trie;
    vector<int> lc;
    vector<int> rc;

    Trie() {
        create();
    }

    int create() {
        trie.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return trie.size() - 1;
    }
 
    void update(int i, int t, int cid) {
        trie[cid]++;
        if (t == -1) return;
        if ((1 << t) & i) {
            if (rc[cid] == -1) rc[cid] = create();
            update(i, t - 1, rc[cid]);
        }
        else {
            if (lc[cid] == -1) lc[cid] = create();
            update(i, t - 1, lc[cid]);
        }
    }

    int query(int a, int t, int cid) {
        if (t == -1) return 0;

        if ((1 << t) & a) {
            if (lc[cid] != -1 && trie[lc[cid]]) {
                return query(a, t - 1, lc[cid]) | (1 << t);
            }
            else if (rc[cid] != -1 && trie[rc[cid]]) {
                return query(a, t - 1, rc[cid]);
            }
            else return 0;
        }
        else {
            if (rc[cid] != -1 && trie[rc[cid]]) {
                return query(a, t - 1, rc[cid]) | (1 << t);
            }
            else if (lc[cid] != -1 && trie[lc[cid]]) {
                return query(a, t - 1, lc[cid]);
            }
            else return 0;
        }
    }
};