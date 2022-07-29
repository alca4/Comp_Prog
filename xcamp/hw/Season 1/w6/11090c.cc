#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <queue>
#include <cstring>
using namespace std;

#define ll long long
typedef pair<int, ll> pii;
int T, N, M;
vector<pii> adjlist[60];
ll d[60][60];
int q[60][60];
int vis[60];

void Search(int a)
{
    d[a][0] = 0;
    q[a][0] = 1;
    queue<pii> search;
    search.push(pii(a, 0));
    while (!search.empty())
    {
        int cur = search.front().first;
        ll k = search.front().second;
        search.pop();
        vis[cur] = 1;
        if (k >= N) continue;

        for (int j = 0; j < adjlist[cur].size(); j++)
        {
            int tar = adjlist[cur][j].first;
            ll w = adjlist[cur][j].second;
            if (d[tar][k + 1] > d[cur][k] + w)
            {
                d[tar][k + 1] = d[cur][k] + w;
                if (!q[tar][k + 1])
                {
                    q[tar][k + 1] = 1;
                    search.push(pii(tar, k + 1));
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> T;
    for (int k = 1; k <= T; k++)
    {
        for (int i = 0; i < 60; i++)
            for (int j = 0; j < 60; j++)
            {
                d[i][j] = 1e18;
                q[i][j] = 0;
            }
        memset(vis, 0, sizeof(vis));
        
        for (int i = 0; i < 60; i++) adjlist[i].resize(0);

        cin >> N >> M;
        for (int i = 0; i < M; i++)
        {
            int a, b;
            ll c;
            cin >> a >> b >> c;
            adjlist[a].push_back(pii(b, c));
        }
        
        for (int i = 1; i <= N; i++)
            if (!vis[i]) Search(i);

        double ans = 1e18;
        for (int i = 1; i <= N; i++)
        {
            if (d[i][N] == 1e18) continue;
            double maxd = 0;
            for (int j = 0; j < N; j++)
            {
                double t = j;
                maxd = max(maxd, (d[i][N] - d[i][j]) / (N - t));
            }
            ans = min(ans, maxd);
        }

        /*
        for (int i = 1; i <= N; i++)
        {
            for (int j = 0; j <= N; j++)
                cout << d[i][j] << " ";
            cout << endl;
        }
        */

        cout << "Case #" << k << ": ";
        if (ans == 1e18) cout << "No cycle found." << endl;
        else cout << fixed << setprecision(2) << ans << endl;
    }
    return 0;
}