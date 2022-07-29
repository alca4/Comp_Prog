/*
Learnings:
DSU Undo
Be careful of loop variables and skipping over ppl!
Multiple structs are fine copium
Test code 1 part at a time -> DO NOT DELETE DEBUG CODE
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;
 
typedef pair<int, int> pii;
 
struct Edge
{
    int n1;
    int n2;
    int id;
    int w;
};
struct Query
{
    vector<Edge> es;
    int id;
    int works = 1;
};
 
int N, M, Q;
Edge e[500010];
 
vector<Edge> used;
int p[500010];
int sz[500010];
 
Query q[500010];
int a[500010];

//unordered_map<vector<Edge>, int> mappy;
 
int Root(int a)
{
    return (a == p[a]) ? a : Root(p[a]);
}
bool Combine(int a, int b)
{
    a = Root(a);
    b = Root(b);
    if (a == b) return false;
    if (sz[b] > sz[a]) swap(a, b);
    //cout << "attaching edge from " << b << " to " << a << endl;
    p[b] = a;
    sz[a] += sz[b];
    Edge e;
    e.n1 = a;
    e.n2 = b;
    used.push_back(e);
    return true;
}
void Undo()
{
    Edge e = used[used.size() - 1];
    used.pop_back();
    if (Root(e.n1) != Root(e.n2)) return;
    //cout << "removing edge from " << e.n2 << " to " << e.n1 << endl;
    sz[e.n1] -= sz[e.n2];
    p[e.n2] = e.n2;
}
 
bool CompW(const Edge& e1, const Edge& e2)
{
    return e1.w < e2.w;
}
bool CompQ(const Query& q1, const Query& q2)
{
    return q1.es[0].w < q2.es[0].w;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
 
    // input graph
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) 
    {
        scanf("%d%d%d", &e[i].n1, &e[i].n2, &e[i].w);
        e[i].id = i;
    }
 
    // input queries
    int qcount = 1;
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) 
    {
        int s;
        scanf("%d", &s);
        vector<Edge> edges;
        for (int j = 1; j <= s; j++) 
        {
            int val;
            scanf("%d", &val);
            edges.push_back(e[val]);
        }
        sort(edges.begin(), edges.end(), CompW);
 
        
        int ub = 1;
        for (int j = 0; j < s; j++)
        {
            Query it;
            while (ub < s && edges[j].w == edges[ub].w) ub++;
            for (; j < ub; j++) it.es.push_back(edges[j]);
            it.id = i;
            q[qcount++] = it;
            j--;
        }
    }
    qcount--;
 
    // prepare Kruskal testing
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;
    sort(e + 1, e + 1 + M, CompW);
    sort(q + 1, q + 1 + qcount, CompQ);

    /*
    for (int i = 1; i <= qcount; i++)
    {
        cout << "Query " << i << " belongs to " << q[i].id << " and contains ";
        for (int j = 0; j < q[i].es.size(); j++)
            cout << q[i].es[j].id << " ";
        cout << endl;
    }
    */
 
    // test
    int ub = 1;
    int c = 1;
    for (int i = 1; i <= M; i++)
    {
        //cout << "new edges" << endl;
        while (ub <= M && e[ub].w == e[i].w) ub++;
        while (c <= qcount && q[c].es[0].w == e[i].w)
        {
            /*
            if (mappy.find(q[c].es) != mappy.end())
            {
                q[c].works = mappy[q[c].es];
                continue;
            }
            */
            //cout << "on query " << c << endl;
            vector<int> worked(q[c].es.size());
            for (int j = 0; j < q[c].es.size(); j++)
            {
                Edge cur = q[c].es[j];
                bool did = Combine(cur.n1, cur.n2);
                worked[j] = did;
                q[c].works = (q[c].works && did);
            } 
            for (int j = 0; j < q[c].es.size(); j++) if (worked[j]) Undo();
            //mappy[q[c].es] = q[c].works;
            //for (int j = 1; j <= N; j++) cout << p[j] << " " << sz[j] << endl;
            c++;
        }
        
        for (; i < ub; i++)
        {
            if (Root(e[i].n1) != Root(e[i].n2))
            {
                //cout << "combining " << e[i].n1 << " and " << e[i].n2 << endl;
                Combine(e[i].n1, e[i].n2);
            }       
        }
        i--;
    }
 
    for (int i = 1; i <= Q; i++) a[i] = 1;
    for (int i = 1; i <= qcount; i++)
    {
        a[q[i].id] = a[q[i].id] && q[i].works;
        //if (q[i].works) cout << "query " << i  << " works " << endl;
    }
        
 
    // output
    for (int i = 1; i <= Q; i++)
    {
        if (a[i]) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}