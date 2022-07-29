#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <bitset>
using namespace std;

typedef pair<int ,int> pii;

struct Info
{
    int loc;
    int p;
    int w;
};

struct Compare
{
    bool operator() (Info& a, Info& b)
    {
        return a.w > b.w;
    }
};

int N, M;
int S = 200;
pii doges[30010];
vector<Info> adjlist[30010][210];
int dist[30010][210];
int psum[30010];

bool CompP(const pii& d1, const pii& d2)
{
    return d1.second < d2.second;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cout.tie(0);

    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++)
    {
        scanf("%d%d", &doges[i].first, &doges[i].second);
        int pval = (doges[i].second > S ? 0 : doges[i].second);
        for (int j = 0; j <= S; j++)
        {
            if (j == pval) continue;
            adjlist[doges[i].first][j].push_back(Info{doges[i].first, pval, 0});
        }
    }

    pii src = doges[0];
    pii dest = doges[1];

    sort(doges, doges + M, CompP);
    int prev = -1;
    for (int i = 0; i < M; i++)
    {
        int l = doges[i].first;
        int p = doges[i].second;
        if (p > S)
        {
            for (int i = (l + p) % p; i < N; i += p)
            {
                adjlist[l][0].push_back(Info{i, 0, abs(l - i) / p});
            }
        }
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j <= S; j++)
            dist[i][j] = 1e9;

    priority_queue<Info, vector<Info>, Compare> pq;
    int pval = (src.second > S ? 0 : src.second);
    pq.push(Info{src.first, pval, 0});
    dist[src.first][pval] = 0;
    while (!pq.empty())
    {
        int cur = pq.top().loc;
        int jump = pq.top().p;
        //cout << cur << " " << jump << endl;
        int d = pq.top().w;
        pq.pop();

        if (dest.first == cur)
        {
            //cout << "found answer" << endl;
            cout << d << endl;
            return 0;
        }

        for (int i = 0; i < adjlist[cur][jump].size(); i++)
        {
            int tar = adjlist[cur][jump][i].loc;
            int tarjump = adjlist[cur][jump][i].p;
            int cost = adjlist[cur][jump][i].w;

            if (d + cost < dist[tar][tarjump])
            {
                //cout << "going to " << tar << " " << tarjump << endl;
                dist[tar][tarjump] = d + cost;
                pq.push(Info{tar, tarjump, dist[tar][tarjump]});
            }
        }
        if (cur + jump < N && d + 1 < dist[cur + jump][jump])
        {
            //cout << "going to " << tar << " " << tarjump << endl;
            dist[cur + jump][jump] = d + 1;
            pq.push(Info{cur + jump, jump, dist[cur + jump][jump]});
        }
        if (cur - jump >= 0 && d + 1 < dist[cur - jump][jump])
        {
            //cout << "going to " << tar << " " << tarjump << endl;
            dist[cur - jump][jump] = d + 1;
            pq.push(Info{cur - jump, jump, dist[cur - jump][jump]});
        }
    }

    cout << -1 << endl;
    return 0;
}