#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define INF 1e9

struct ST
{
    int tot = 0;
    vector<int> seg;
    vector<int> lc;
    vector<int> rc;

    ST() {tot = 1;}
    ST(int sz)
    {
        tot = sz;
        seg.push_back(-INF);
        lc.push_back(-1);
        rc.push_back(-1);
    }

    void Update(int a, int c) 
    {
        int d = 0;
        Update(a, c, d, 0, tot);
    }
    void Update(int a, int c, int& cid, int ss, int se)
    {
        if (cid < 0) 
        {
            cid = seg.size();
            seg.push_back(-INF);
            lc.push_back(-1);
            rc.push_back(-1);
        }

        if (ss == se)
        {
            seg[cid] = c;
            return;
        }
        
        int mid = (ss + se) / 2;
        if (a <= mid) 
        {
            int left = lc[cid];
            Update(a, c, left, ss, mid);
            lc[cid] = left;
        }
        else 
        {
            int right = rc[cid];
            Update(a, c, right, mid + 1, se);
            rc[cid] = right;
        }
        int ans = -INF;
        if (lc[cid] != -1) ans = max(ans, seg[lc[cid]]);
        if (rc[cid] != -1) ans = max(ans, seg[rc[cid]]);
        seg[cid] = ans;
    }

    int Query(int a, int b) {return Query(a, b, 0, 0, tot);}
    int Query(int a, int b, int cid, int ss, int se)
    {
        if (cid < 0) return -INF;
        if (a <= ss && se <= b) 
        {
            //for (int i = 0; i < seg.size(); i++) cout << seg[i] << " ";
            //cout << endl;
            //cout << "returning: " << seg[cid] << endl;
            return seg[cid];
        }

        int mid = (ss + se) / 2;
        int ans = -INF;
        if (a <= mid) ans = max(ans, Query(a, b, lc[cid], ss, mid));
        if (b >= mid + 1) ans = max(ans, Query(a, b, rc[cid], mid + 1, se));
        return ans;
    }
};

int N, M;
ST dists[100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) dists[i] = ST(100000);
    while (M--)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int q = dists[a].Query(0, c - 1);
        //cout << "query returned: " << q << endl;
        if (q < 0) q = 0;
        dists[b].Update(c, q + 1);
    }
    int mval = 0;
    for (int i = 1; i <= N; i++) 
        mval = max(mval, dists[i].Query(0, 100000));
    cout << mval << endl;
    return 0;
}