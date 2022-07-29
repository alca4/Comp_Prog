#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, int> pii;

int N, Q;
int ans[100010];
int vis[100010];
set<int> adjlist[100010];
pii q[200010];
vector<pii> roads;

void Fill(int start, int val)
{
    queue<int> search;
    search.push(start);
    vis[start] = 1;
    while (!search.empty())
    {
        int a = search.front();
        //cout << "looking at " << a << endl;
        search.pop();

        if (ans[a] == -1) 
        {
            //cout << "got " << a << endl;
            ans[a] = val;
        }
        for (auto n : adjlist[a]) 
            if (!vis[n])
            {
                search.push(n);
                vis[n] = 1;
            }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    
    cin >> N >> Q;
    roads.resize(1); // so we can 1-index
    for (int i = 1; i <= N; i++) ans[i] = Q;
    for (int i = 1; i <= Q; i++)
    {
        char c;
        cin >> c;
        if (c == 'A')
        {
            int a, b;
            cin >> a >> b;
            roads.push_back(pii(a, b));
            adjlist[a].insert(b);
            adjlist[b].insert(a);
            q[i] = pii(0, 0);
        }
        if (c == 'D')
        {
            int a;
            cin >> a;
            ans[a] = -1;
            q[i] = pii(1, a);
        }
        if (c == 'R')
        {
            int a;
            cin >> a;
            adjlist[roads[a].first].erase(roads[a].second);
            adjlist[roads[a].second].erase(roads[a].first);
            q[i] = pii(2, a);
        }
    }

    for (int i = 1; i <= N; i++)
        if (ans[i] != -1)
            Fill(i, Q);

    for (int i = Q; i >= 1; i--)
    {
        //cout << i << endl;
        if (q[i].first == 1)
            Fill(q[i].second, i - 1);
        if (q[i].first == 2)
        {
            int a = roads[q[i].second].first;
            int b = roads[q[i].second].second;
            adjlist[a].insert(b);
            adjlist[b].insert(a);
            if (ans[a] != -1 || ans[b] != -1) Fill(a, i - 1);
        }
    }
    for (int i = 1; i <= N; i++) cout << ans[i] << endl;
    return 0;
}