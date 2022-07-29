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
ll dist[60];
int in_queue[60];
int times_added[60];

bool SPFA(ll w, int start)
{
    queue<int> search;
    search.push(start);
    in_queue[start] = 1;
    times_added[start] = 1;
    dist[start] = 0;
    while (!search.empty())
    {
        int cur = search.front();
        //cout << "adding " << cur << endl;
        in_queue[cur] = 0;
        search.pop();

        if (times_added[cur] == N) return true;
        for (int i = 0; i < adjlist[cur].size(); i++)
        {
            int tar = adjlist[cur][i].first;
            ll tw = adjlist[cur][i].second;

            if (dist[tar] > dist[cur] + tw - w)
            {
                dist[tar] = dist[cur] + tw - w;
                if (!in_queue[tar]) 
                {
                    in_queue[tar] = 1;
                    search.push(tar);
                    times_added[tar]++;
                }
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        cin >> N >> M;
        for (int j = 1; j <= M; j++)
        {
            //cout << j << endl;
            int a, b;
            ll c;
            cin >> a >> b >> c;
            adjlist[a].push_back(pii(b, c * 1e9));
        }
        ll lo = 0;
        ll hi = 1e18;
        ll num = 1e18;
        while (lo <= hi)
        {
            for (int i = 0; i <= 60; i++) dist[i] = 1e18;
            memset(in_queue, 0, sizeof(in_queue));
            memset(times_added, 0, sizeof(times_added));
            for (int i = 1; i <= N; i++)
            {
                cout << dist[i] << " " << in_queue[i] << " " << times_added[i] << endl;
            }
            
            ll mid = (lo + hi) / 2;
            cout << lo << " " << hi << " " << mid << endl;
            bool neg = 0;
            for (int j = 1; j <= N; j++) 
                if (times_added[j] == 0)
                    neg = neg || SPFA(mid, j);
            if (neg) 
            {
                hi = mid - 1;
                num = min(num, mid);
            }
            else lo = mid + 1;
            for (int i = 1; i <= N; i++)
            {
                cout << dist[i] << " " << in_queue[i] << " " << times_added[i] << endl;
            }
        }
        cout << "Case #" << i << ": ";
        if (num == 1e18) cout << "No cycle found." << endl;
        else
        {
            //num /= 10;
            double ans = num / 1e9;
            cout << fixed << setprecision(2) << ans << endl;
        }
        for (int j = 1; j <= N; j++) adjlist[j].resize(0);
    }
}