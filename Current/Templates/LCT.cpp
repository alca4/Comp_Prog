
struct Line
{
    ll m, b;

    ll valueAt(int x)
    {
        return m * x + b;
    }

    ld intersect(const Line& other)
    {
        return 1.0 * (other.b - b) / (m - other.m);
    }
};

struct Node
{
    Line l;
    int lc = -1, rc = -1;
};

struct LCT
{
    Node seg[4 * MAXN];

    void insert(Line l, int cid, int ss, int se)
    {
        int mid = (ss + se) / 2;

        bool dl = l.valueAt(ss) < seg[cid].l.valueAt(ss);
        bool dm = l.valueAt(mid) < seg[cid].l.valueAt(mid);

        if (dm) 
        {
            Line temp = l;
            l = seg[cid].l;
            seg[cid].l = temp;
        }

        if (ss == se) return;
        else if (dl != dm) insert(l, seg[cid] * 2, ss, mid);
        else insert(l, seg[cid] * 2 + 1, mid + 1, se);
    }

    ll query(int a, int cid, int ss, int se)
    {
        ll ans = seg[cid].l.valueAt(a);
        if (ss == se) return ans;

        ll mid = (ss + se) / 2;
        if (a <= mid) ans = min(ans, query(a, seg[cid] * 2, ss, mid));
        else ans = min(ans, query(a, seg[cid] * 2 + 1, mid + 1, se));
        return ans;
    }
};