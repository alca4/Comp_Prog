#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

#define ll long long
typedef pair<int, int> pii;

struct Range
{
    int s;
    int e;
    ll v;

    Range() {s = e = v = 0;}
    Range(int a, int b, ll val) {s = a, e = b, v = val;}
};
struct Node
{
    Range ans;
    ll sum;
    Range left;
    Range right;
};
Node Combine(const Node& n1, const Node& n2)
{
    Node other;
    other.sum = n1.sum + n2.sum;

    ll maxs = max(max(n1.ans.v, n2.ans.v), n1.right.v + n2.left.v);
    if (maxs == n1.ans.v) other.ans = n1.ans;
    else if (maxs == n2.ans.v) other.ans = n2.ans;
    else other.ans = Range(n1.right.s, n2.left.e, n1.right.v + n2.left.v);

    ll maxl = max(n1.left.v, n1.sum + n2.left.v);
    if (maxl == n1.left.v) other.left = n1.left;
    else other.left = Range(n1.left.s, n2.left.e, n1.sum + n2.left.v);

    ll maxr = max(n2.right.v, n2.sum + n1.right.v);
    if (maxr == n2.right.v) other.right = n2.right;
    else other.right = Range(n1.right.s, n2.right.e, n2.sum + n1.right.v);
    return other;
}

struct Segment
{
    int sz;
    vector<Node> seg;
    vector<int> rev;

    Segment(vector<ll>& vec)
    {
        sz = vec.size() - 1;
        seg.resize(sz * 4);
        rev.resize(sz * 4);
        Build(vec, 1, 1, sz);
    }

    void Build(vector<ll>& vec, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid].sum = vec[ss];
            seg[cid].ans = Range(cid, cid, vec[ss]);
            seg[cid].left = Range(cid, cid, vec[ss]);
            seg[cid].right = Range(cid, cid, vec[ss]);
        } 
            
        else
        {
            int mid = (ss + se) / 2;
            Build(vec, cid * 2, ss, mid);
            Build(vec, cid * 2 + 1, mid + 1, se);
            seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
        }
    }

    ll Query(int a, int b) {return Query(a, b, 1, 1, sz).ans.v;}
    Node Query(int a, int b, int cid, int ss, int se)
    {
        if (rev[cid])
        {
            seg[cid].Reverse();
            if (ss != se)
            {
                rev[cid * 2] = !rev[cid * 2];
                rev[cid * 2 + 1] = !rev[cid * 2 + 1];
            }
        }
        if (a <= ss && se <= b) 
        {
            Node temp = seg[cid];
            rev[cid] = 1;
            seg[cid].Reverse();
            if (ss != se)
            {
                rev[cid * 2] = !rev[cid * 2];
                rev[cid * 2 + 1] = !rev[cid * 2 + 1];
            }
            return temp;
        }
        Node empty;
        empty.Equals(0);
        if (se < a || b < ss || ss == se) return empty;
        int mid = (ss + se) / 2;
        seg[cid] = Combine(Query(a, b, cid * 2, ss, mid),  
                           Query(a, b, cid * 2 + 1, mid + 1, se));
        return seg[cid];
    }

    void Reverse(int a, int b) {Reverse(a, b, 1, 1, sz);}
    void Reverse(int a, int b, int cid, int ss, int se)
    {
        if (rev[cid] == 1)
        {
            seg[cid].Reverse();
            if (ss != se)
            {
                rev[cid * 2] = !rev[cid * 2];
                rev[cid * 2 + 1] = !rev[cid * 2 + 1];
            }
        }
        if (se < a || a < ss || ss == se) return;
        int mid = (ss + se) / 2;
    	Reverse(a, b, cid * 2, ss, mid);
    	Reverse(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void Update(int a, int n) {Update(a, 1, 1, sz, n);}
    void Update(int a, int cid, int ss, int se, int n)
    {
        if (ss == se && ss == a) 
        {
            seg[cid].Equals(n);
            return;
        }
        if (se < a || a < ss || ss == se) return;
        int mid = (ss + se) / 2;
    	Update(a, cid * 2, ss, mid, n);
    	Update(a, cid * 2 + 1, mid + 1, se, n);
        seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void Print()
    {
        for (int i = 1; i < seg.size(); i++)
            printf("%lld ", seg[i].sum);
        printf("\n");
    }
};

int N, Q;
vector<ll> vals;

int main()
{
    scanf("%d", &N);
    vals.resize(N + 1);
    for (int i = 1; i <= N; i++) scanf("%lld", &vals[i]);
    Segment s(vals);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++)
    {
        int t;
        scanf("%d", &t);
        if (t == 0) 
        {
            int a, n;
            scanf("%d%d", &a, &n);
            s.Update(a, n);
        }
        if (t == 1) 
        {
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);
            ll ans = 0;
            for (int j = 1; j <= k; j++)
            {
                ll cur = s.Query(a, b);
                cout << cur << endl;
                if (cur <= 0) break;
                ans += cur;
            }
            s = Segment(vals);
            //s.Reverse(a, b);
            s.Print();
            printf("%lld\n", ans);
        }
    }
    return 0;
}