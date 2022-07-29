#include<iostream>
#include<vector>
#include<bitset>
#include<stack>
#include<cmath>
#include<set>
#include<algorithm>
using namespace std;

int N;
int adjmat[5010][5010];
int vis[5010];

bool DFS(int cur, int prev)
{
    vis[cur] = 1;
    for (int i = 1; i <= N; i++)
    {
        if (!adjmat[cur][i]) continue;
        if (prev != -1 && adjmat[i][prev])
        {
            cout << prev << " " << cur << " " << i << endl;
            return true;
        }
        if (!vis[i] && DFS(i, cur)) return true;
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        string str;
        cin >> str;
        for (int j = 1; j <= N; j++)
            adjmat[i][j] = str[j - 1] - '0';
    }

    for (int i = 1; i <= N; i++)
    {
        if (vis[i]) continue;
        if (DFS(i, -1)) return 0;
    }

    cout << -1 << endl;
    return 0;
}