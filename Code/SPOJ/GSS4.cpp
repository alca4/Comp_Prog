#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

#define ll long long

struct Node
{
    ll sum = 0;
    ll m = 0;
};

Node Combine(const Node& n1, const Node& n2)
{
    Node other;
    other.sum = n1.sum + n2.sum;
    other.m = max(n1.m, n2.m);
    return other;
}

struct Segment
{
    int size;
    vector<Node> seg;

    Segment(const vector<ll>& vec)
    {
        size = vec.size() - 1;
        seg.resize(vec.size() * 4);
        build(vec, 1, 1, size);
    }

    void build(const vector<ll>& vec, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid].sum = vec[ss];
            seg[cid].m = vec[ss];
        }
        else
        {
            int mid = (ss + se) / 2;
            build(vec, cid * 2, ss, mid);
            build(vec, cid * 2 + 1, mid + 1, se);
            seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
        }
    }

    ll Query(int a, int b) {return Query(a, b, 1, 1, size);}

    ll Query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid].sum;
        if (a > se || ss > b) return 0;
        int mid = (ss + se) / 2;
        return Query(a, b, cid * 2, ss, mid) +
               Query(a, b, cid * 2 + 1, mid + 1, se);
    }
    
    void Update(int a, int b) {Update(a, b, 1, 1, size);}
    
    void Update(int a, int b, int cid, int ss, int se)
    {
    	if (seg[cid].m == 1) return;
    	if (ss == se && a <= ss && ss <= b)
    	{
    		seg[cid].sum = sqrt(seg[cid].sum);
    		seg[cid].m = seg[cid].sum;
    	}
    	if (a > se || ss > b || ss == se) return;
    	int mid = (ss + se) / 2;
    	Update(a, b, cid * 2, ss, mid);
    	Update(a, b, cid * 2 + 1, mid + 1, se);
    	seg[cid] = Combine(seg[cid * 2], seg[cid * 2 + 1]);
    }
    
    void Print()
    {
    	for (int i = 1; i <= seg.size(); i++)
            cout << seg[i].sum << " ";
        cout << endl;
    }
};

int N, Q;
vector<ll> vals;

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	int count = 1;
    while (scanf("%d",&N) != EOF)
    {
    	printf("Case #%d:\n", count++);
        vals.resize(0);
        vals.resize(N + 1);
        for (int i = 1; i <= N; i++)
            scanf("%lld", &vals[i]);
        Segment s(vals);
        scanf("%d", &Q);
        for (int i = 1; i <= Q; i++)
        {
        	int t, a, b;
        	scanf("%d%d%d", &t, &a, &b);
        	if (a > b) swap(a, b);
        	if (t == 0) s.Update(a, b);
        	if (t == 1) printf("%lld\n", s.Query(a, b));
        }
        printf("\n");
    }
    return 0;
}