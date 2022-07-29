#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
using namespace std;

int N, M, Q;
const int S = 950;
struct Query{int t, n1, n2;};
bool CompQ(const Query& q1, const Query& q2) {return q1.n2 < q2.n2;};
Query qs[100010];

struct Edge {int n1, n2, w;};
bool CompE(const Edge& e1, const Edge& e2) {return e1.w < e2.w;};
Edge edges[100010];
int out[100010];

int p[50010], sz[50010];
stack<int> dsu;
int root(int a)
{
    return (a == p[a] ? a : root(p[a]));
}
bool combine(Edge e)
{
    int a = root(e.n1);
    int b = root(e.n2);
    if (a == b) return 0;
    if (sz[a] > sz[b])
    {
        dsu.push(b);
        sz[a] += sz[b];
        p[b] = a;
    }
    else
    {
        dsu.push(a);
        sz[b] += sz[a];
        p[a] = b;
    }
    return 1;
}
void undo()
{
    int b = dsu.top();
    dsu.pop();
    sz[root(b)] -= sz[b];
    p[b] = b;
}

int ans[100010];
int temp[100010];

int main()
{
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;
    for (int i = 1; i <= M; i++) 
        scanf("%d%d%d", &edges[i].n1, &edges[i].n2, &edges[i].w);

    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) 
        scanf("%d%d%d", &qs[i].t, &qs[i].n1, &qs[i].n2);

    for (int i = 1; i <= Q; i += S)
    {
        while (!dsu.empty()) undo();
        for (int j = 1; j <= M; j++) out[j] = 0;

        int ub = min(Q, i + S - 1);

        vector<Edge> same;
        vector<Query> queries;
        for (int j = i; j <= ub; j++) 
        {
            if (qs[j].t == 1) out[qs[j].n1] = 1;
            else queries.push_back({j * -1, qs[j].n1, qs[j].n2});
        }
        for (int j = 1; j <= M; j++)
            if (!out[j]) same.push_back(edges[j]);
        
        sort(same.rbegin(), same.rend(), CompE);
        sort(queries.begin(), queries.end(), CompQ);

        int sid = 0;
        vector<int> sc;
        while (sid < same.size() && queries.size() > 0 && same[sid].w >= queries[0].n2)
            sc.push_back(combine(same[sid++]));
        
        for (int j = 0; j < queries.size(); j++)
        {
            for (int k = i; k <= ub; k++)
                if (qs[k].t == 1)
                {
                    temp[qs[k].n1] = edges[qs[k].n1].w;
                }
            while (sid > 0 && same[sid - 1].w < queries[j].n2) 
            {
                sid--;
                if (sc[sid] == 1) undo();
            }
            for (int k = i; k <= ub; k++)
                if (qs[k].t == 1) 
                    if (k < queries[j].t * -1) temp[qs[k].n1] = qs[k].n2;
            
            int dused = 0;
            for (int k = i; k <= ub; k++)
            {
                if (qs[k].t == 1 && temp[qs[k].n1] >= queries[j].n2)
                    dused += combine(edges[qs[k].n1]);
            }
            ans[queries[j].t * -1] = sz[root(queries[j].n1)];
            for (int k = 0; k < dused; k++) undo();
        }
        for (int j = i; j <= ub; j++)
            if (qs[j].t == 1)
                edges[qs[j].n1].w = qs[j].n2;
    }
    for (int i = 1; i <= Q; i++)
        if (ans[i] != 0)
            cout << ans[i] << endl;
    return 0;
}