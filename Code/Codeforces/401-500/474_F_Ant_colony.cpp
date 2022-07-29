#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node
{
    int num_min = 0;
    int gcd = -1;
};

int Euclid(int a, int b)
{
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return Euclid(b, a % b);
}

Node Combine(const Node& n1, const Node& n2)
{
    if (n1.gcd == -1) return n2;
    if (n2.gcd == -1) return n1;
    Node other;
    other.gcd = Euclid(n1.gcd, n2.gcd);
    //cout << other.gcd << " = gcd of " << n1.gcd << " " << n2.gcd << endl;
    if (n1.gcd == other.gcd) other.num_min += n1.num_min;
    if (n2.gcd == other.gcd) other.num_min += n2.num_min;
    return other;
}

struct Segment
{
    int size;
    vector<Node> seg;

    Segment(vector<int>& v)
    {
        size = v.size() - 1;
        seg.resize(size * 4);
        Build(v, 1, 1, size);
    }

    void Build(vector<int>& v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid].num_min = 1;
            seg[cid].gcd = v[ss];
            return;
        }

        int mid = (ss + se) / 2;
        Build(v, cid * 2, ss, mid);
        Build(v, cid * 2 + 1, mid + 1, se);
        seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node Query(int a, int b) {return Query(a, b, 1, 1, size);}
    Node Query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) 
        {
            /*
            cout << "returning from " << ss << " to " << se << endl;
            cout << "gcd is: " << seg[cid].gcd << endl;
            cout << "has " << seg[cid].num_min << " gcds" << endl;
            */
            return seg[cid];
        }
        if (b < ss || se < a) return Node();

        int mid = (ss + se) / 2;
        return Combine(Query(a, b, cid * 2, ss, mid), Query(a, b, cid * 2 + 1, mid + 1, se));
    }
};

int N, T;
vector<int> a;

int main()
{
    scanf("%d", &N);
    a.resize(N + 1);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);
    Segment s(a);
    scanf("%d", &T);
    for (int i = 1; i <= T; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        //cout << s.Query(a, b).gcd << endl;
        printf("%d\n", b - a + 1 - s.Query(a, b).num_min);
    }
    return 0;
}