#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;

int N;
int w[200010];
int e[200010];
int vis[200010];

int DP(int cur, stack<int>& path)
{
    if (vis[cur])
    {
        //cout << cur << " duplicate" << endl;
        int minv = w[cur];
        while (path.top() != cur)
        {
            minv = min(minv, w[path.top()]);
            path.pop();
            if (path.size() == 0) return 0;
        }
        //cout << "returning " << minv << endl;
        return minv;
    }
    path.push(cur);
    vis[cur] = 1;
    return DP(e[cur], path);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> w[i];
    for (int i = 1; i <= N; i++) cin >> e[i];

    long long total = 0;
    for (int i = 1; i <= N; i++)
    {
        if (vis[i]) continue;
        //cout << "doing stuff from " << i << endl;
        stack<int> path;
        total += DP(i, path);
        //cout << total << endl;
    }

    cout << total << endl;
    return 0;
}