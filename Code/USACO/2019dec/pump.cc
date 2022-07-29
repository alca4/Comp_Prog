#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef pair<double, piii> info;

int N, M;
vector<vector<piii>> adjList;
double dist[1001];

int main()
{
    ifstream fin ("pump.in");
    fin >> N >> M;
    adjList.resize(N + 1);
    for (int i = 1; i <= N; i++) dist[i] = 0;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        double c, d;
        fin >> a >> b >> c >> d;
        adjList[a].push_back(piii(b, pii(d, c)));
        adjList[b].push_back(piii(a, pii(d, c)));
    }

    priority_queue<pair<double, piii>> pq;
    pq.push(info(0, piii(1, pii(1e9, 0))));
    while (!pq.empty())
    {
        double val = pq.top().first * -1;
        int dest = pq.top().second.first;
        double flow = pq.top().second.second.first;
        double cost = pq.top().second.second.second;
        pq.pop();
        cout << dest << endl;

        cout << val << " " << dist[dest] << endl;
        if (val < dist[dest] * -1) continue;

        for (int i = 0; i < adjList[dest].size(); i++)
        {
            int nd = adjList[dest][i].first;
            double f = adjList[dest][i].second.first;
            double c = adjList[dest][i].second.second;
            double v = min(flow, f) / (cost + c) * -1;
            cout << min(flow, f) << " over " << cost + c << " is " << v << endl;
            cout << "considering going to " << nd << endl;

            if (v < dist[nd])
            {
                dist[nd] = v;
                cout << "pushing" << endl;
                pq.push(info(v, piii(nd, pii(min(flow, f), cost + c))));
            }
        }
    }

    cout << dist[N] << endl;

    return 0;
}