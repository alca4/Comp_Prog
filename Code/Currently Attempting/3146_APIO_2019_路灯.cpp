#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

int N, Q;

struct Node
{
    int t, lazy, lc, rc;
};

struct SegTree
{
    vector<Node> seg;

    SegTree() {create();}

    int create()
    {
        seg.push_back({0, 0, -1, -1});
        return seg.size() - 1;
    }

    int apply(int v, int cid)
    {
        if (cid == -1) cid = create();
        seg[cid].lazy = v;
        seg[cid].t = v;
        return cid;
    }
    void push(int cid, int ss, int se)
    {
        if (ss != se)
        {
            seg[cid].lc = apply(seg[cid].lazy, seg[cid].lc);
            seg[cid].rc = apply(seg[cid].lazy, seg[cid].rc);
            seg[seg[cid].lc].t = seg[seg[cid].rc].t = seg[cid].t;
        }
    }
    int fill(int a, int b, int v, int cid, int ss, int se)
    {
        if (cid != -1) cid = create();
        Node& cur = seg[cid];

        if (a <= ss && se <= b)
        {
            apply(v,cid);
            seg[cid].t = v;
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;

        if (a <= mid) cur.lc = fill(a, b, v, cur.lc, ss, mid);
        if (b > mid) cur.rc = fill(a, b, v, cur.rc, mid + 1, se);
        return cid;
    }
};

SegTree vals[300010];
SegTree state[300010];
set<int> off;

void update(int x1, int x2, int y1, int y2, int v)
{
    while (x2 > 0)
    {
        state[x2].fill(y1, y2, v, 1, 1, N);
        x2 -= (x2 & -x2);
    }
    x1--;
    while (x1 > 0)
    {
        state[x1].fill(y1, y2, 1 - v, 1, 1, N);
        x1 -= (x1 & -x1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    string init;
    cin >> init;
    for (int i = 0; i < N; i++) if (!init[i]) off.insert(i + 1);
    N++;
    for (int i = 1; i <= N; i++) state[i].create();

    for (int i = 1; i <= Q; i++)
    {
        string str;
        if (str == "toggle")
        {
            int a;
            cin >> a;
            auto it = off.lower_bound(a);
            if (*(it) == a)
            {
                // turn on
                int l = *(--it) + 1;
                int r = *(++++it);
                update(l, a, a + 1, r, 1);
                off.erase(a);
            }
            else
            {
                // turn off
                int l = *(--it) + 1;
                int r = *(++it);
                update(l, a, a + 1, r, 0);
                off.insert(a);
            }
        }
        else
        {
            int a, b;
            cin >> a >> b;
            cout << state[a].query(b, 1, 1, N) << endl;
        }
    }
}