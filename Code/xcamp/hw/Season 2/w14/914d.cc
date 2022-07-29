#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int gcd(int a, int b)
{
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct ST
{
    int sz;
    vector<int> seg;

    ST(vector<int>& v)
    {
        sz = v.size() - 1;
        seg.resize(4 * sz);
        Build(v, 1, 1, sz);
    }

    void Build(vector<int>& v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v[ss];
            return;
        }

        int mid = (ss + se) / 2;
        Build(v, cid * 2, ss, mid);
        Build(v, cid * 2 + 1, mid + 1, se);
        seg[cid] = gcd(seg[cid * 2], seg[cid * 2 + 1]);
    }

    int Query(int a, int b, int x) {return Query(a, b, x, 1, 1, sz);}
    int Query(int a, int b, int x, int cid, int ss, int se)
    {
        if (se < a || b < ss) return 0;
        if (ss == se) return (seg[cid] % x == 0) ? 0 : 1;
        
        int mid = (ss + se) / 2;
        if (seg[cid * 2 + 1] % x == 0) return Query(a, b, x, cid * 2, ss, mid);
        if (seg[cid * 2] % x == 0) return Query(a, b, x, cid * 2 + 1, mid + 1, se);
        if (a <= ss && se <= b) return 2;
        return Query(a, b, x, cid * 2, ss, mid) + Query(a, b, x, cid * 2 + 1, mid + 1, se);
    }

    void Update(int a, int n) {Update(a, n, 1, 1, sz);}
    void Update(int a, int n, int cid, int ss, int se)
    {
        if (ss == se && ss == a) 
        {
            seg[cid] = n;
            return;
        }
        if (a < ss || se < a || ss == se) return;

        int mid = (ss + se) / 2;
        if (a <= mid) Update(a, n, cid * 2, ss, mid);
        else Update(a, n, cid * 2 + 1, mid + 1, se);
        seg[cid] = gcd(seg[cid * 2], seg[cid * 2 + 1]);
    }
};

int N, M;
vector<int> vals;

int main()
{
    /*
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    */

    scanf("%d", &N);
    vals.resize(N + 1);
    for (int i = 1; i <= N; i++) scanf("%d", &vals[i]);
    ST s(vals);
    /*
    for (int i = 1; i < s.seg.size(); i++) cout << s.seg[i] << " ";
    cout << endl;
    */

    scanf("%d", &M);
    while (M--)
    {
        int type;
        scanf("%d", &type);
        if (type == 1)
        {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);
            if (s.Query(l, r, v) < 2) printf("YES\n");
            else printf("NO\n");
            //cout << s.Query(l, r, v) << endl;
        }
        else
        {
            int a, v;
            scanf("%d%d", &a, &v);
            //cout << a << endl;
            s.Update(a, v);
            /*
            for (int i = 1; i < s.seg.size(); i++) cout << s.seg[i] << " ";
    		cout << endl;
    		*/
        }
    }
}