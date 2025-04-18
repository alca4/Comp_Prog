/*
Idea: graph + segtree
use segments as nodes so you can efficient connect planets using 2 & 3rd type guns
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#define ll long long
typedef pair<ll, ll> pii;

int N, Q, S;
#define t2 400000
#define t3 800000
vector<pii> adjlist[1500010];
ll dist[1500010];

void build(int cid, int ss, int se)
{
    if (ss == se) 
    {
        adjlist[cid + t2].push_back(pii(cid, 0));
        adjlist[cid + t3].push_back(pii(cid, 0));
        adjlist[cid].push_back(pii(cid + t2, 0));
        adjlist[cid].push_back(pii(cid + t3, 0));
        return;
    }

    int mid = (ss + se) / 2;
    build(cid * 2, ss, mid);
    build(cid * 2 + 1, mid + 1, se);
    adjlist[cid + t2].push_back(pii(cid * 2 + t2, 0));
    adjlist[cid + t2].push_back(pii(cid * 2 + 1 + t2, 0));
    adjlist[cid * 2 + t3].push_back(pii(cid + t3, 0));
    adjlist[cid * 2 + 1 + t3].push_back(pii(cid + t3, 0));
}

void traverse(int a, int b, int src, int v, int t, int cid, int ss, int se)
{
    if (a <= ss && se <= b)
    {
        if (t == 2) adjlist[src].push_back(pii(cid + t2, v));
        if (t == 3) adjlist[cid + t3].push_back(pii(src, v));
        return;
    }

    int mid = (ss + se) / 2;
    if (a <= mid) traverse(a, b, src, v, t, cid * 2, ss, mid);
    if (b > mid) traverse(a, b, src, v, t, cid * 2 + 1, mid + 1, se);
}

int query(int a, int cid, int ss, int se)
{
    if (ss == se) return cid;

    int mid = (ss + se) / 2;
    if (a <= mid) return query(a, cid * 2, ss, mid);
    else return query(a, cid * 2 + 1, mid + 1, se);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q >> S;
    build(1, 1, N);
    for (int i = 0; i < Q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            ll v, u, w;
            cin >> v >> u >> w;
            adjlist[query(v, 1, 1, N)].push_back(pii(query(u, 1, 1, N), w));
        }
        else
        {
            ll v, l, r, w;
            cin >> v >> l >> r >> w;
            traverse(l, r, query(v, 1, 1, N), w, t, 1, 1, N);
        }
    }

    for (int i = 1; i <= 1500000; i++) dist[i] = 1e18;

    priority_queue<pii> pq;
    int src = query(S, 1, 1, N);
    dist[src] = 0;
    pq.push(pii(0, src));
    while (!pq.empty())
    {
        ll d = pq.top().first * -1;
        int cur = pq.top().second;
        //cout << cur << " " << d << endl;
        pq.pop();

        for (int i = 0; i < adjlist[cur].size(); i++)
        {
            int tar = adjlist[cur][i].first;
            ll cost = adjlist[cur][i].second;
            
            if (d + cost < dist[tar])
            {
                dist[tar] = d + cost;
                //cout << "going to " << tar << " with cost " << dist[tar] << endl;
                
                pq.push(pii(dist[tar] * -1, tar));
            }
        }
    }

    for (int i = 1; i <= N; i++) 
    {
        ll ans = dist[query(i, 1, 1, N)];
        cout << (ans == 1e18 ? -1 : ans) << " ";
    }
    
    cout << endl;
    return 0;
}