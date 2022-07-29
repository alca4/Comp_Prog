#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
using namespace std;

int N, root;
vector<vector<int>> edges(100001);
bitset<100001> visited;
int depth[100001];
int height[100001];
int farmers[100001];

void FindDepth(int root)
{
    queue<int> bfs;
    bfs.push(root);
    depth[root] = 0;
    while (!bfs.empty())
    {
        int n = bfs.front();
        bfs.pop();
        visited.flip(n);
        for (int i = 0; i < edges[n].size(); i++)
        {
            if (!visited[edges[n][i]])
            {
                bfs.push(edges[n][i]);
                depth[edges[n][i]] = depth[n] + 1;
            }
        }
    }
}

int FindHeight(int node)
{
    visited.flip(node);
    if (edges[node].size() == 1) return 0;
    int min_height = 1e9;
    for (int i = 0; i < edges[node].size(); i++)
    {
        if (!visited[edges[node][i]])
        {
            min_height = min(min_height, FindHeight(edges[node][i]));
        }
    }
    height[node] = min_height + 1;
    return min_height + 1;
}

int FindFarmers(int node)
{
    visited.flip(node);
    if (depth[node] < height[node])
    {
        int farmers = 0;
        for (int i = 0; i < edges[node].size(); i++)
        {
            if (!visited[edges[node][i]])
            {
                farmers += FindFarmers(edges[node][i]);
            }
        }
        return farmers;
    }
    else return 1;
}

int main()
{
    ifstream fin("atlarge.in");
    fin >> N >> root;
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        fin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);

    }
    FindDepth(root);
    visited.reset();
    height[root] = FindHeight(root);
    visited.reset();
    ofstream fout ("atlarge.out");
    fout << FindFarmers(root) << endl;
    return 0;
}