#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct Edge
{
    Edge(long long wp, int n1p, int n2p)
    {
        w = wp, n1 = n1p, n2 = n2p;
    }

    long long w;
    int n1;
    int n2;

    bool operator <(const Edge& e2)
    {
        return w < e2.w;
    }
};

typedef pair<int, int> pii;
const int MAXN = 100010;
int N;
pii moos[MAXN];
int p[MAXN];
int r[MAXN];
vector<Edge> edgelist;

int Root(int a)
{
    return (p[a] == a) ? a : Root(p[a]);
}

void Combine(int a, int b)
{
    a = Root(a), b = Root(b);
    if (a == b) return;
    if (r[a] > r[b])
        p[b] = a;
    else
    {
        if (r[a] == r[b]) r[b]++;
        p[a] = b;
    }
}

long long Dist(int a, int b)
{
    long long c = pow(moos[a].first - moos[b].first, 2) + 
        		  pow(moos[a].second - moos[b].second, 2);
    //cout << c << endl;
    return c;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++) 
        cin >> moos[i].first >> moos[i].second, p[i] = i, r[i] = 0;
        
    sort(moos + 1, moos + 1 + N);    
    
    for (int i = 1; i <= N; i++)
    {
    	//cout << "checking edges for " << i << endl;
        int min_zero_dist = 20;
        int min_zero_id;
        if (i > 1)
        {
            int l = i - 1;
            int al;
            long long d = 1e18;
            int ml = moos[i].first - sqrt(d);
            bool goes_left = false;
            while (l > 0 /*&& moos[l].first >= ml*/)
            {
            	//cout << "checking " << l << endl;
                if (moos[l].first == moos[i].first) 
                {
                    if (min_zero_dist > abs(moos[l].second - moos[i].second))
                    {
                        min_zero_dist = abs(moos[l].second - moos[i].second);
                        min_zero_id = l;
                    }
                }
                else if (d > Dist(i, l))
                {
                    d = Dist(i, l);
                    al = l;
                }
                l--;
            }
            //cout << "considering edge from " << i << " to " << al << endl;
            if (d < 1e18) edgelist.push_back(Edge(d, i, al));
        }
        if (i < N)
        {
            int r = i + 1;
            int ar;
            long long d = 1e18;
            int mr = moos[i].first + sqrt(d);
            while (r <= N /*&& moos[r].first <= mr*/)
            {
            	//cout << "checking " << r << endl;
                if (moos[r].first == moos[i].first) 
                {
                    if (min_zero_dist > abs(moos[r].second - moos[i].second))
                    {
                        min_zero_dist = abs(moos[r].second - moos[i].second);
                        min_zero_id = r;
                    }
                }
                else if (d > Dist(i, r))
                {
                    d = Dist(i, r);
                    ar = r;
                }
                r++;
            }
            //cout << "considering edge from " << i << " to " << ar << endl;
            if (d < 1e18) edgelist.push_back(Edge(d, i, ar));
        }
        if (min_zero_dist != 20)
        {
        	//cout << "considering edge from " << i << " to " << min_zero_id << endl;
        	edgelist.push_back(Edge(pow(min_zero_dist, 2), i, min_zero_id));
        }
            
    }
    
    sort(edgelist.begin(), edgelist.end());

    long long ans = 0;
    int id = 0;
    int count = 0;
    //cout << edgelist.size() << endl;
    while (count < N - 1 && id < edgelist.size())
    {
        long long w = edgelist[id].w;
        int n1 = edgelist[id].n1;
        int n2 = edgelist[id].n2;
        id++;
        //cout << "considering length " << w << " between " << n1 << " and " << n2 << endl;

        if (Root(n1) == Root(n2)) continue;
        count++;
        //cout << "chose length " << w << " between " << n1 << " and " << n2 << endl;
        ans += w;
        Combine(n1, n2);
    }

    cout << ans << endl;
    return 0;
}