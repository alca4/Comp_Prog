#include<iostream>
#include<fstream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;
typedef vector<pii> vpii;
typedef vector<vi> vii;

int N, M, T;
int cows[10001];
long dist[10001];
vii child;
int inflow[10001];
vector<vpii> AdjList;

int Inflow(int i)
{
    int ans = cows[i];
    for (int j = 0; j < child[i].size(); j++) ans += Inflow(child[i][j]);
    inflow[i] = ans;
    return ans;
}

int main()
{
    ifstream fin ("shortcut.in");
    fin >> N >> M >> T;
    AdjList.resize(N + 1);
    child.resize(N + 1);
    for (int i = 1; i <= N; i++) 
    {
        fin >> cows[i];
        dist[i] = -1e18;
    }
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        fin >> a >> b >> c;
        AdjList[a].push_back(pii(b, c));
        AdjList[b].push_back(pii(a, c));
    }

    priority_queue<piii> pq;
    pq.push(piii(0, pii(-1, -1)));
    while (!pq.empty())
    {
        int d = pq.top().first;
        int from = pq.top().second.first;
        int cur = pq.top().second.second;
        pq.pop();

        if (d <= dist[cur * -1]) continue;
        dist[cur * -1] = d;

        if (from != cur) child[from * -1].push_back(cur * -1);
        /*
        cout << "using edge from " << from * -1
             << " to " << cur * -1 << " with dist being " << d * -1 << endl;
        */

        for (int i = 0; i < AdjList[cur * -1].size(); i++)
        {
            int t = AdjList[cur * -1][i].first * -1;
            int cost = AdjList[cur * -1][i].second * -1;
            pq.push(piii(d + cost, pii(cur, t)));
        }
    }

    Inflow(1);
    //for (int i = 1; i <= N; i++) cout << inflow[i] << endl;
    long ans = 0;
    for (int i = 1; i <= N; i++) ans = max(ans, inflow[i] * (dist[i] * -1 - T));
    ofstream fout ("shortcut.out");
    fout << ans << endl;
    return 0;
}