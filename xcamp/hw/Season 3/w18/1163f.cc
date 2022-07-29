#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define ll long long
#define INF 1000000000000000000
typedef pair<ll, ll> pii;

struct Edge
{
    int n1;
    int n2;
    int w;
};

int N, M, Q;
vector<pii> adjlist[200010];
Edge edgelist[200010];
ll dist[200010][2];
int pre[200010][2];
ll lr[200010][2];
ll seg[800010];
ll lazy[800010];

void build(int cid, int ss, int se)
{
    lazy[cid] = INF;
    if (ss == se)
    {
        seg[cid] = INF;
        return;
    }

    int mid = (ss + se) / 2;
    build(cid * 2, ss, mid);
    build(cid * 2 + 1, mid + 1, se);
    seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
}

void apply(ll v, int child)
{
    lazy[child] = min(lazy[child], v);
    seg[child] = min(lazy[child], seg[child]);
}

void push(int cid, int ss, int se)
{
    if (lazy[cid] == INF) return;
    if (ss != se)
    {
        apply(lazy[cid], cid * 2);
        apply(lazy[cid], cid * 2 + 1);
    }
    lazy[cid] = INF;
}

void update(int a, int b, ll v, int cid, int ss, int se)
{
    if (a > se || b < ss || se < ss) return;
    if (a <= ss && se <= b)
    {
        apply(v, cid);
        return;
    }
    push(cid, ss, se);
    int mid = (ss + se) / 2;
    if (a <= mid) update(a, b, v, cid * 2, ss, mid);
    if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
    seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
}

ll query(int a, int b, int cid, int ss, int se)
{
    if (a <= ss && se <= b) return seg[cid];
    push(cid, ss, se);
    int mid = (ss + se) / 2;
    ll ans = INF;
    if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
    if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
    seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    return ans;
}

void Dijkstra(int src, int type)
{
    priority_queue<pii> pq;
    pq.push(pii(0, src));
    dist[src][type] = 0;
    while (!pq.empty())
    {
        ll d = pq.top().first * -1;
        int cur = pq.top().second;
        pq.pop();
 
        if (d > dist[cur][type]) continue;
        
        for (int i = 0; i < adjlist[cur].size(); i++)
        {
            int tar = adjlist[cur][i].first;
            ll cost = adjlist[cur][i].second;
 
            if (d + cost < dist[tar][type])
            {
                dist[tar][type] = d + cost;
                pre[tar][type] = cur;
                pq.push(pii(dist[tar][type] * -1, tar));
            }
        }
    }
}

int Trace(int src, int dest, int type, int inc)
{
    if (lr[dest][type] != INF) return lr[dest][type];
    return lr[dest][type] = Trace(src, pre[dest][type], type, inc) + inc;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;
    for (int i = 1; i <= M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adjlist[a].push_back(pii(b, c));
        adjlist[b].push_back(pii(a, c));
        edgelist[i] = {a, b, c};
    }

    for (int i = 1; i <= N; i++) 
        dist[i][0] = dist[i][1] = lr[i][0] = lr[i][1] = INF;

    Dijkstra(1, 0);
    Dijkstra(N, 1);

    for (int i = 1; i <= M; i++)
    {
        Edge e = edgelist[i];
        if (dist[e.n1][0] + dist[e.n2][1] >
            dist[e.n1][1] + dist[e.n2][0])
            edgelist[i] = {e.n2, e.n1, e.w};
    }

    int onpath = Trace(1, N, 0, 1);
    Trace(N, 1, 1, 1);
    for (int i = N - 1; i >= 1; i--) Trace(1, i, 0, 0);
    for (int i = 2; i <= N; i++) Trace(N, i, 1, 0);

    build(1, 1, onpath - 1);
    for (int i = 1; i <= M; i++)
    {
        Edge e = edgelist[i];
        ll tempw = dist[e.n1][0] + e.w + dist[e.n2][1];
        
        if (tempw != dist[1][1])
            update(lr[e.n1][0], onpath - lr[e.n2][1], tempw, 1, 1, onpath - 1);
    }

    while (Q--)
    {
        int id, d;
        cin >> id >> d;
        Edge e = edgelist[id];
        ll tempw = dist[e.n1][0] + e.w + dist[e.n2][1];
        ll ans;
        if (tempw > dist[1][1]) 
        {
            //cout << "type 1" << endl;
            ans = min(tempw - e.w + d, dist[1][1]);
        }
        else
        {
            if (d < e.w) 
            {
                //cout << "type 2" << endl;
                ans = dist[1][1] - e.w + d;
            }
            else 
            {
                //cout << "type 3" << endl;
                ll q = query(lr[e.n1][0], onpath - lr[e.n2][1], 1, 1, onpath - 1);
                ans = min(q, dist[1][1] - e.w + d);
            }
        }
        cout << ans << endl;
    }
    return 0;
}