#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

struct Edge
{
    int n1, n2;
    ll w;
};

const int MAXN = 100010, MAXM = 200010;
int N, M, Q;
Edge edges[MAXM];
ll dist[MAXN][30];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= 20; j++) dist[i][j] = INF;
    for (int i = 1; i <= M; i++) 
    {
        cin >> edges[i].n1 >> edges[i].n2 >> edges[i].w;
        if (edges[i].n1 < edges[i].n2) swap(edges[i].n1, edges[i].n2);
        int cnt = 0;
        int tmp = edges[i].n1;
        while (tmp != edges[i].n2)
        {
            tmp = (tmp >> 1);
            cnt++;
        }
        dist[edges[i].n1][cnt] = edges[i].w;
    }

    for (int i = 2; i <= N; i++)
    {
        int tmp = i;
        int cnt = 0;
        while (tmp != 1)
        {
            tmp = (tmp >> 1);
            cnt++;
            for (int t2 = 1; t2 < cnt; t2++)
                dist[i][cnt] = min(dist[i][cnt], dist[i][t2] + dist[(i >> t2)][cnt - t2]);
            for (int t2 = 1; t2 < cnt; t2++)
                dist[(i >> t2)][cnt - t2] = min(dist[(i >> t2)][cnt - t2], 
                                                dist[i][t2] + dist[i][cnt]);
        }
    }

    for (int i = 2; i <= N; i++)
    {
        int tmp = i;
        int cnt = 0;
        while (tmp != 1)
        {
            tmp = (tmp >> 1);
            cnt++;
            for (int t2 = 1; t2 < cnt; t2++)
                dist[i][cnt] = min(dist[i][cnt], dist[i][t2] + dist[(i >> t2)][cnt - t2]);
            for (int t2 = 1; t2 < cnt; t2++)
                dist[(i >> t2)][cnt - t2] = min(dist[(i >> t2)][cnt - t2], 
                                                dist[i][t2] + dist[i][cnt]);
        }
    }

    cin >> Q;
    while (Q--)
    {
        int a, b;
        cin >> a >> b;
        
        int /*best*/ ta = a, tb = b;
        int acnt = 0;
        int bcnt = 0;
        while (ta != tb)
        {
            if (ta > tb) 
            {
                ta = (ta >> 1);
                acnt++;
            }
            if (tb > ta) 
            {
                tb = (tb >> 1);
                bcnt++;
            }
        }

        ll ans = INF;
        while (ta > 0)
        {
            ans = min(ans, dist[a][acnt] + dist[b][bcnt]);
            ta = (ta >> 1);
            acnt++;
            bcnt++;
        }
        if (ans == INF) cout << -1 << endl;
        else cout << ans << endl;
    }
    return 0;
}