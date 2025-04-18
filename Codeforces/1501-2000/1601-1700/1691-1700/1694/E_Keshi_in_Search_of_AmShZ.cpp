/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
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
#include <bitset>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010, MAXM = 200010;
int N, M;
vector<int> nbs[MAXN];
int dist[MAXN];
int vis[MAXN];
int rem[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int a = read();
        int b = read();
        nbs[b].pb(a);
        rem[a]++;
    }
    for (int i = 1; i <= N; i++) dist[i] = INF;
    
    priority_queue<pii> pq;
    pq.push({0, N});
    dist[N] = 0;
    while (!pq.empty())
    {
        int n = pq.top().S;
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i];
            rem[tar]--;
            if (dist[n] + rem[tar] + 1 < dist[tar])
            {
                dist[tar] = dist[n] + rem[tar] + 1;
                pq.push({-1 * dist[tar], tar});
            }
        }
    }

    cout << dist[1] << endl;
    return 0;
}