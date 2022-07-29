#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int N, M, K;
vector<vector<pii>> adjList;
vi bales;
vi d;
int usedBale[100000];

int main()
{
    ifstream fin ("dining.in");
    fin >> N >> M >> K;
    adjList.resize(N + 1);
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        fin >> a >> b >> c;
        adjList[a].push_back(pii(b, c));
        adjList[b].push_back(pii(a, c));
    }
    bales.assign(N + 1, 0);
    for (int i = 0; i < K; i++)
    {
        int a, b;
        fin >> a >> b;
        bales[a] = b;
    }
    d.assign(N + 1, 1e9);

    // used haybale, distance, node
    priority_queue<piii> pq;
    d[N] = 0;
    pq.push(piii(0, pii(0, N)));
    while (!pq.empty())
    {
        piii temp = pq.top();
        pq.pop();
        int hasBale = temp.first;
        int dist = temp.second.first;
        int cur = temp.second.second;
        
        if (d[cur] < dist || d[cur]) continue;

        for (int i = 0; i < adjList[cur].size(); i++)
        {
            pii edge = adjList[cur][i];
            if (d[cur] + edge.second < d[edge.first])
            {
                d[edge.first] = d[cur] + edge.second;
                usedBale[edge.first] = hasBale;
                pq.push(piii(hasBale, pii(d[edge.first], edge.first)));
            }
            if (hasBale == 0)
            {
                if (d[cur] + edge.second - bales[edge.first] <= d[edge.first])
                {
                    d[edge.first] = d[cur] + edge.second - bales[edge.first];
                    usedBale[edge.first] = 1;
                    pq.push(piii(1, pii(d[edge.first], edge.first)));
                }
            }
        }
    }

    ofstream fout ("dining.out");
    for (int i = 1; i < N; i++) fout << usedBale[i] << endl;
    return 0;
}