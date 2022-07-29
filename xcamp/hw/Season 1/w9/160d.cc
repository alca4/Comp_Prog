/*
LEARNINGS:
If you don't know where a bug is reduce the amount of code that is written
*/

#include<iostream>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
typedef pair<int, int> pii;

struct Edge
{
    int n1;
    int n2;
    int id;
    int w;
    int ans;
};
 
int N, M, Q;
Edge e[100010];
int p[100010];

set<int> g[100010];
set<int> n;
int vis[100010];
int num[100010];
int lo[100010];

int Root(int a)
{
    int r = a;
    while (p[r] != r) r = p[r];
    int i = a;
    int j;
    while (i != r)
    {
        j = p[i];
        p[i] = r;
        i = j;
    }
    return r;
}

bool Combine(int a, int b)
{
    a = Root(a);
    b = Root(b);
    if (a == b) return false;
    //cout << "attaching edge from " << b << " to " << a << endl;
    p[b] = a;
    return true;
}

bool CompW(const Edge& e1, const Edge& e2)
{
    return e1.w < e2.w;
}
bool CompId(const Edge& e1, const Edge& e2)
{
    return e1.id < e2.id;
}

int counter = 0;
void Tarjan(int cur, int prev)
{
    num[cur] = ++counter;
    vis[cur] = 1;
    lo[cur] = num[cur];
    for (auto tar : g[cur])
    {
        if (!vis[tar]) Tarjan(tar, cur);
        if (tar != prev) lo[cur] = min(lo[cur], lo[tar]);
    }
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
        e[i].ans = 400;
    }
 
    // prepare Kruskal testing
    for (int i = 1; i <= N; i++) p[i] = i;
    sort(e + 1, e + 1 + M, CompW);

    // test
    int ub = 1;
    for (int i = 1; i <= M; i++)
    {
        //cout << e[i].w << endl;
        while (ub <= M && e[ub].w == e[i].w) ub++;

        // Checking which edges are none
        for (int j = i; j < ub; j++)
            if (Root(e[j].n1) == Root(e[j].n2)) e[j].ans = 0;

        // Inputting the graph
        for (int j = i; j < ub; j++)
        {
            if (e[j].ans != 0)
            {
                g[e[j].n1].insert(e[j].n2);
                g[e[j].n2].insert(e[j].n1);

                g[e[j].n1].insert(p[e[j].n1]);
                g[p[e[j].n1]].insert(e[j].n1);

                g[e[j].n2].insert(p[e[j].n2]);
                g[p[e[j].n2]].insert(e[j].n2);

                n.insert(e[j].n1);
                n.insert(e[j].n2);
                n.insert(p[e[j].n1]);
                n.insert(p[e[j].n2]);
            }
        }

        // Clearing visited
        for (auto t : n)
        {
            vis[t] = 0;
            lo[t] = 0;
            num[t] = 0;
        }
            
        // Tarjan's
        counter = 0;
        for (auto t : n)
            if (!vis[t]) Tarjan(t, -1);
        
        // Checking for bridge
        for (int j = i; j < ub; j++)
        {
            if (e[j].ans != 0)
            {
                int n1 = e[j].n1;
                int n2 = e[j].n2;
                if (lo[n1] > num[n2] || lo[n2] > num[n1])
                {
                    e[j].ans = 2;
                    /*
                    cout << "Edge " << j << " from " << e[j].n1 << " to "
                         << e[j].n2 << " with weight " << e[j].w 
                         << " is a bridge " << endl;
                    */
                }
                else
                    e[j].ans = 1;
            }
        }

        // Resetting
        for (auto t : n)
        {
            vis[t] = 0;
            lo[t] = 0;
            num[t] = 0;
            g[t].clear();
        }
        n.clear();

        for (; i < ub; i++) Combine(e[i].n1, e[i].n2);
        i--;
    }

    sort(e + 1, e + 1 + M, CompId);
 
    // output
    for (int i = 1; i <= M; i++)
    {
        /*
        cout << "Edge " << i << " from " << e[i].n1 << " to "
             << e[i].n2 << " with weight " << e[i].w << " appears in ";
        */
        if (e[i].ans == 2) printf("any\n");
        if (e[i].ans == 1) printf("at least one\n");
        if (e[i].ans == 0) printf("none\n");
    }
    return 0;
}