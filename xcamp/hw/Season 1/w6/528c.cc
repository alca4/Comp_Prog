#include<iostream>
#include<algorithm>
#include<stack>
#include<set>
#include<vector>
#include<map>
using namespace std;

#define v vector
typedef pair<int, int> pii;

const int MAXN = 100010;
int N, M;
multiset<int> adjlist[MAXN];
int deg[MAXN];
v<pii> edges;

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjlist[a].insert(b);
        adjlist[b].insert(a);
        deg[a]++;
        deg[b]++;
    }

    v<int> fix;
    for (int i = 1; i <= N; i++)
    {
        if (deg[i] % 2 != 0)
        {
            fix.push_back(i);
            if (fix.size() == 2)
            {
                adjlist[fix[0]].insert(i);
                adjlist[i].insert(fix[0]);
                fix.resize(0);
            }
        }
    }

    stack<int> cur;
    stack<int> complete;
    cur.push(1);
    while (!cur.empty())
    {
        int n = cur.top();
        if (adjlist[n].size() == 0) 
        {
            complete.push(n);
            cur.pop();
        }
        else
        {
            int nb = *adjlist[n].begin();
            adjlist[n].erase(adjlist[n].begin());
            adjlist[nb].erase(adjlist[nb].find(n));
            cur.push(nb);
        }
    }

    vector<int> path;
    while (!complete.empty())
    {
        path.push_back(complete.top());
        complete.pop();
    }

    if (path.size() % 2 == 0) path.push_back(1);
    cout << path.size() - 1 << endl;
    for (int i = 0; i < path.size() - 1; i++)
    {
        if (i % 2 == 0) cout << path[i] << " " << path[i + 1] << endl;
        else cout << path[i + 1] << " " << path[i] << endl;
    }
    return 0;
}