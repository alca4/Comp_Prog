#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

typedef pair<int, int> pii;

int N, M;
vector<vector<pii>> out_edges(N + 1);
vector<vector<pii>> in_edges(N + 1);
bitset<100001> visited;
vector<int> top_sort;

int Indeg(int i, int limit)
{
    int ans = 0;
    for (int j = 0; j < in_edges[i].size(); j++)
    {
        if (in_edges[i][j].second <= limit && !visited[in_edges[i][j].second]) 
        {
            ans++;
        }
    }
    cout << i << " has indegree " << ans << endl;
    return ans;
}

bool Acyclic(int limit)
{
    cout << "checking if " << limit << " is acyclic" << endl;
    queue<int> search;
    for (int i = 1; i <= N; i++)
    {
        if (Indeg(i, limit) == 0) search.push(i);
    }
    if (search.empty()) return false;
    while (!search.empty())
    {
        int n = search.front();
        //cout << "searching node " << n << endl;
        if (visited[n]) return false;
        visited.set(n, true);
        search.pop();
        for (int i = 0; i < out_edges[n].size(); i++)
        {
            if (Indeg(out_edges[n][i].first, limit) == 1)
            {
                search.push(out_edges[n][i].first);
            }
        }
    }
    visited.reset();
    return true;
}

void TopSort(int limit)
{
    queue<int> search;
    for (int i = 1; i <= N; i++)
    {
        if (Indeg(i, limit) == 0) search.push(i);
    }
    while (!search.empty())
    {
        int n = search.front();
        top_sort.push_back(n);
        //cout << "searching node " << n << endl;
        visited.set(n, true);
        search.pop();
        for (int i = 0; i < out_edges[n].size(); i++)
        {
            if (Indeg(out_edges[n][i].first, limit) == 1)
            {
                search.push(out_edges[n][i].first);
            }
        }
    }
    visited.reset();
}

int main()
{
    ifstream fin ("milkorder.in");
    fin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int m;
        fin >> m;
        vector<int> obs(m);
        for (int j = 0; j < m; j++)
        {
            fin >> obs[j];
            if (j > 0) 
            {
                in_edges[obs[j - 1]].push_back(pii(obs[j], i));
                out_edges[obs[j]].push_back(pii(obs[j - 1], i));                
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        sort(out_edges[i].begin(), out_edges[i].end());
        sort(in_edges[i].begin(), in_edges[i].end());
        for (int j = 0; j < out_edges[i].size(); j++)
        {
            cout << i << " is connected to " << out_edges[i][j].first << endl;
        }
    }
    
    int lb = 0;
    int ub = M - 1;
    int ans;
    while (lb <= ub)
    {
        int mid = (lb + ub) / 2;
        if (Acyclic(mid)) 
        {
            //cout << mid << " is acyclic" << endl;
            ans = mid;
            lb = mid + 1;
        }
        else ub = mid - 1;
    }
    //cout << "ans is " << ans << endl;

    cout << "performing topological sort" << endl;
    TopSort(ans);
    for (int i = 0; i < N; i++)
    {
        cout << top_sort[i] << endl;
    }
    return 0;
}