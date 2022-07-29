#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct Node
{
    long p = 0;
    long s = 0;
    long a = 0;
    long r = 0;
    bool exists = 0;

    Node() {}

    Node(long p2, long s2, long a2, long r2) 
    {
        p = p2; s = s2; a = a2; r = r2; exists = true;
    }
};

struct Segment
{
    vector<Node> seg;
    int size;

    Segment(int N)
    {
        if (pow(2, floor(log(N) / log(2))) == N) size = 2 * N;
        else size = 2 * pow(2, floor(log(N) / log(2) + 1));
        seg.resize(size);
        size = N;
    }

    Node Combine(const Node& n1, const Node& n2)
    {
        Node ans;
        if (!n1.exists && !n2.exists) return ans;
        if (!n1.exists) return n2;
        if (!n2.exists) return n1;
        ans.a = max(max(n1.a, n2.a), n1.s + n2.p);
        ans.p = max(n1.p, n1.r + n2.p);
        ans.s = max(n2.s, n2.r + n1.s);
        ans.r = n1.r + n2.r;
        ans.exists = true;
        return ans;
    }

    void PU(int i, int n)
    {
        PU(1, size, 1, i, n);
    }

    void PU(int ss, int se, int cid, int i, int n)
    {
        if (i < ss || i > se) return;
        if (ss == se)
        {
            if (ss == i)
            {
                seg[cid].p = n;
                seg[cid].s = n;
                seg[cid].r = n;
                seg[cid].a = n;
                seg[cid].exists = true;
            }
            return;
        }
        PU(ss, (ss + se) / 2, cid * 2, i, n);
        PU((ss + se) / 2 + 1, se, cid * 2 + 1, i, n);
        seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    long RQ(int s1, int e1, int s2, int e2)
    {
        if (e1 < s2 - 1)
            return Range(s1, e1).s + Range(e1 + 1, s2 - 1).r + Range(s2, e2).p;
        else if (e1 == s2 - 1)
            return Range(s1, e1).s + Range(s2, e2).p;
        else 
        {
            Node b = Range(s2, e1);
            Node c = Range(e1 + 1, e2);
            long a_bc_ = Range(s1, s2 - 1).s + Combine(b, c).p;
            long b_ = b.a;
            long b_c = b.s + c.p;
            return max(max(a_bc_, b_), b_c);
        }
    }

    Node Range(int i, int j)
    {
        return Range(1, size, 1, i, j);
    }

    Node Range(int ss, int se, int cid, int i, int j)
    {
        Node ans;
        if (i <= ss && j >= se) return seg[cid];
        if (i > se || j < ss || ss == se) return ans;
        return Combine(Range(ss, (ss + se) / 2, cid * 2, i, j),
                       Range((ss + se) / 2 + 1, se, cid * 2 + 1, i, j));
    }
};

int T;

int main()
{
    cin >> T;
    for (int i = 0; i < T; i++)
    {
    	int N, M;
        cin >> N;
        Segment s(N);
        for (int j = 1; j <= N; j++) 
        {
            int a;
            cin >> a;
            s.PU(j, a);
        }
        cin >> M;
        for (int j = 0; j < M; j++)
        {
            int s1, e1, s2, e2;
            cin >> s1 >> e1 >> s2 >> e2;
            cout << s.RQ(s1, e1, s2, e2) << endl;
        }
    }
    return 0;
}