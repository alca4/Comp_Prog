#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

#define ll long long

struct Node
{
    int t;
    int v1;
    ll v2;
};

struct SSeg
{
    vector<Node> seg;
    vector<int> l1;
    vector<int> l2;
    vector<int> lc;
    vector<int> rc;

    SSeg() {create();}

    int create()
    {
        seg.push_back({0, 0, 0});
        l1.push_back(0);
        l2.push_back(0);
        lc.push_back(-1);
        rc.push_back(-1);
        return seg.size() - 1;
    }

    int a1(ll val, int cid, int ss, int se)
    {
        if (cid == -1) cid = create();
        l1[cid] = 1;
        seg[cid].v1 = (se - ss + 1);
        return cid;
    }
    void p1(int cid, int ss, int se)
    {
        if (l1[cid] == 0) return;
        if (ss != se) 
        {
            int mid = (ss + se) / 2;
            lc[cid] = a1(l1[cid], lc[cid], ss, mid);
            rc[cid] = a1(l1[cid], rc[cid], mid + 1, se);
        }
        l1[cid] = 0;
    }
    int u1(int a, int b, ll v, int cid, int ss, int se)
    {
        if (cid == -1) cid = create();
        if (a <= ss && se <= b)
        {
            a1(v, cid, ss, se);
            return cid;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) lc[cid] = u1(a, b, v, lc[cid], ss, mid);
        if (b > mid) rc[cid] = u1(a, b, v, rc[cid], mid + 1, se);
        ll ans = 0;
        if (lc[cid] != -1) ans += seg[lc[cid]].v1;
        if (rc[cid] != -1) ans += seg[rc[cid]].v1;
        seg[cid].v1 = ans;
        return cid;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}