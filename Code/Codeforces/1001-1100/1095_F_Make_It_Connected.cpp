#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define v vector
#define ll long long

struct Edge
{
    ll v1;
    ll v2;
    ll w;
};

int N, M;
ll w[200010];
int p[200010];
int r[200010];
vector<Edge> edges;

int Root(int a)
{
    return (a == p[a] ? a : Root(p[a]));
}

void Combine(int a, int b)
{
    a = Root(a);
    b = Root(b);
    if (r[a] < r[b])
        p[a] = b;
    else
    {
        if (r[a] == r[b]) r[a]++;
        p[b] = a;
    }
}

bool CompW(const Edge& e1, const Edge& e2)
{
    return e1.w < e2.w;
}

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> w[i];
    edges.resize(M);
    for (int i = 0; i < M; i++) 
        cin >> edges[i].v1 >> edges[i].v2 >> edges[i].w;

    int minId = 0;
    ll minVal = 1e18;
    for (int i = 1; i <= N; i++)
        if (w[i] < minVal) minVal = w[i], minId = i;

    for (int i = 1; i <= N; i++)
    {
        if (i == minId) continue;
        Edge e;
        e.v1 = minId;
        e.v2 = i;
        e.w = w[i] + w[minId];
        edges.push_back(e);
    }

    for (int i = 1; i <= N; i++) p[i] = i, r[i] = 0;

    sort(edges.begin(), edges.end(), CompW);
    ll total = 0;
    int chosen = 0;
    for (int i = 0; i <= edges.size(); i++)
    {
        if (chosen == N - 1) break;
        int v1 = edges[i].v1;
        int v2 = edges[i].v2;
        ll w = edges[i].w;
        if (Root(v1) == Root(v2)) continue;
        //cout << "used edge between " << v1 << " and " << v2 << endl;
        Combine(v1, v2);
        total += w;
        chosen++;
    }

    cout << total << endl;
    return 0;
}