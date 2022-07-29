#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

typedef vector<long> vi;

struct Node
{
    long a;
    long p;
    long s;
    long r;

    Node()
    {
        a = -1e18, p = -1e18, s = -1e18, r = -1e18;
    }

    Node(long w, long x, long y, long z)
    {
        a = w;
        p = x;
        s = y;
        r = z;
    }

    bool Exists() const
    {
        return (a != -1e18 || p != -1e18 || s != -1e18 || r != -1e18);
    }
};

struct Segment
{
    int size;
    vector<Node> seg;

    Segment(int N)
    {
        if (pow(2, (int) (log(N) / log(2))) == N) 
        {
            size = 2 * N - 1;
            seg.resize(size);
        }
        else
        {
            size = 2 * pow(2, (int) (log(N) / log(2)) + 1) - 1;
            seg.resize(size);
        }
        size = N;
    }

    Node Combine(const Node& n1, const Node& n2)
    {
        Node ans;
        if (!n1.Exists() && !n2.Exists()) return ans;
        if (!n1.Exists()) return n2;
        if (!n2.Exists()) return n1;
        ans.a = max(n2.p + n1.s, max(n1.a, n2.a));
        ans.r = n1.r + n2.r;
        ans.p = max(n1.p, n1.r + n2.p);
        ans.s = max(n2.s, n2.r + n1.s);
        return ans;
    }

    void PU(int id, int d)
    {
        PU(1, size, 1, id, d);
    }

    
    void PU(int ss, int se, int cid, int id, int d)
    {
        if (ss > id || se < id) return;
        if (ss == se)
        {
            if (ss == id)
            {
                Node temp(d, d, d, d);
                seg[cid] = temp;
            }
            return;
        }
        int m = (ss + se) / 2;
        PU(ss, m, cid * 2, id, d);
        PU(m + 1, se, cid * 2 + 1, id, d);
        seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    long RQ(int i, int j)
    {
        return RQ(1, size, 1, i, j).a;
    }

    Node RQ(int ss, int se, int cid, int i, int j)
    {
        //cout << "considering range " << ss << " to " << se << endl;
        if (i <= ss && j >= se) 
        {
            //cout << "found good match" << endl;
            return seg[cid];
        }
        Node ans;
        if (j < ss || i > se || ss == se) 
        {
            //cout << "returning" << endl;
            return ans;
        }
        int m = (ss + se) / 2;
        Node a = RQ(ss, m, cid * 2, i, j);
        /*
        cout << a.a << " " << a.p << " "
             << a.s << " " << a.r << endl;
        */
        Node b = RQ(m + 1, se, cid * 2 + 1, i, j);
        /*
        cout << b.a << " " << b.p << " "
             << b.s << " " << b.r << endl;
        */
        ans = Combine(a, b);
        return ans;
    }
};

int N, M;

int main()
{
    cin >> N;
    Segment stree(N);
    for (int i = 1; i <= N; i++)
    {
        int a;
        cin >> a;
        stree.PU(i, a);
        /*
        for (int i = 1; i < 2 * N; i++) 
            cout << stree.seg[i].s << " ";
        cout << endl;
        */
    }
    cin >> M;
    vi ans(M);
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        ans[i] = stree.RQ(a, b);
    }
    for (int i = 0; i < M; i++) cout << ans[i] << endl;
    return 0;
}