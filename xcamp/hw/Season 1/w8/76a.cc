#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define ll long long

struct Edge
{
    int c1;
    int c2;
    ll g;
    ll s;
    int id;
    bool c = false;
} edges[50010];
ll N, M, G, S;
int p[210];
int sz[210];
vector<Edge> selected;

int Root(int a)
{
    return (a == p[a] ? a : Root(p[a]));
}
bool Combine(int a, int b)
{
    a = Root(a);
    b = Root(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] += sz[b];
    p[b] = a;
    return true;
}

bool CompG(const Edge& e1, const Edge& e2)
{
    return (e1.g == e2.g ? e1.s < e2.s : e1.g < e2.g);
}
bool CompS(const Edge& e1, const Edge& e2)
{
    return (e1.s == e2.s ? e1.g < e2.g : e1.s < e2.s);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> G >> S;
    for (int i = 1; i <= M; i++)
    {
        cin >> edges[i].c1 >> edges[i].c2 >> edges[i].g >> edges[i].s;
        edges[i].id = i;
    }
    
    sort(edges + 1, edges + 1 + M, CompG);
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;

    int chosen = 0;
    ll max_b = 0;
    for (int i = 1; i <= M; i++)
    {
        if (!Combine(edges[i].c1, edges[i].c2)) continue;
        max_b = max(max_b, edges[i].s);
        edges[i].c = 1;
        chosen++;
        selected.push_back(edges[i]);
    }
    if (chosen != N - 1)
    {
        cout << -1 << endl;
        return 0;
    }
    
    /*
    for (int i = 0; i < selected.size(); i++)
    {
        cout << "Using edge " << selected[i].id << endl;
    }
    */

    sort(selected.begin(), selected.end(), CompG);
    ll ans = selected[selected.size() - 1].g * G + max_b * S;
    //cout << "using minimum gold yields " << ans << endl;
    sort(selected.begin(), selected.end(), CompS);
    
    for (int j = 1; j <= M; j++)
    {
        //cout << endl;
        //cout << "On edge " << edges[j].id << " " << endl;
        // Reset DSU
        for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;
        if (edges[j].c) 
        {
            //cout << "edge already chosen" << endl;
            continue;
        } 
        if (!Combine(edges[j].c1, edges[j].c2)) 
        {
            //cout << "edge is a self loop" << endl;
            continue;
        }

        int index_fail = -1;
        for (int i = 0; i < selected.size(); i++)
        {
            if (!Combine(selected[i].c1, selected[i].c2)) 
            {
                if (index_fail != -1) index_fail = -2;
                else index_fail = i;
            }
        }
        if (index_fail == -2) 
        {
            //cout << "this shouldn't happen" << endl;
            continue;
        }
        //cout << "may replace " << selected[index_fail].id << endl;
        if (edges[j].s > selected[index_fail].s)
        {
            //cout << "edge has higher silver value than " << endl;
            continue;
        }
        selected.erase(selected.begin() + index_fail);
        selected.push_back(edges[j]);
        /*
        cout << "selected now contains indices ";
        for (int i = 0; i < selected.size(); i++)
        {
            cout << selected[i].id << " ";
        }
        cout << endl;
        */
        sort(selected.begin(), selected.end(), CompS);
        ll max_g = 0;
        for (int i = 0; i < selected.size(); i++) max_g = max(max_g, selected[i].g);
        ll maybe = max_g * G + selected[selected.size() - 1].s * S;
        //cout << "temp ans is " << maybe << endl;
        ans = min(ans, maybe);
    }

    cout << ans << endl;
    return 0;
}