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
#include <cstring>
#include <cassert>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 1010;
int N, M, P;
vector<pii> nbs[MAXN];
int dp[MAXN][1050];
int ans[1050];
int best[1050];
map<int, int> bit;
int G;
map<int, vector<int>> groups;

int dijkstra(int mask)
{
    set<pii> s;
    for (int i = 1; i <= N; i++) s.insert({dp[i][mask], i});
    // cout << a << " " << mask << endl;
    int ret = s.begin()->FF;
    while (!s.empty())
    {
        int n = s.begin()->SS;
        s.erase(s.begin());

        for (int i = 0; i < nbs[n].size(); i++)
        {
            int tar = nbs[n][i].FF;
            int w = nbs[n][i].SS;

            if (dp[n][mask] + w < dp[tar][mask])
            {
                int old = dp[tar][mask];
                dp[tar][mask] = dp[n][mask] + w;
                s.erase({old, tar});
                s.insert({dp[tar][mask], tar});
            }
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P;
    for (int i = 1; i <= M; i++) 
    {
        int a = read(), b = read(), c = read();
        nbs[a].pb({b, c});
        nbs[b].pb({a, c});
    }

    for (int i = 0; i < P; i++)
    {
        int a = read(), b = read();
        bit[b] = i;
        groups[a].pb(b);
    }
    G = groups.size();

    for (int i = 1; i <= N; i++) for (int j = 1; j < (1 << P); j++)
        dp[i][j] = INF;
    
    for (auto n : bit) dp[n.first][(1 << n.second)] = 0;

    for (int i = 1; i < (1 << P); i++)
    {
        // cout << i << endl;
        for (int n = 1; n <= N; n++)
        {
            for (int x = i; x;) 
            {
                --x &= i;
                if (x != 0 && x != i) 
                {
                    // cout << x << " " << (i ^ x) << endl;
                    dp[n][i] = min(dp[n][i], dp[n][x] + dp[n][i ^ x]);
                }
            }
        }
        ans[i] = dijkstra(i);
    }

    for (int j = 1; j < (1 << G); j++) 
    {
        best[j] = INF;
        int tmp = j;
        int m = 0;
        while (tmp > 0)
        {
            int id = (int) (log2(j & -tmp)) + 1;
            for (int i = 0; i < groups[id].size(); i++) m += (1 << bit[groups[id][i]]);
            tmp -= (tmp & -tmp);
        }
        best[j] = ans[m];
        for (int x = j; x;)
        {
            --x &= j;
            if (x == 0 || x == j) continue;
            // cout << best[x] << " " << best[x ^ j] << endl;
            best[j] = min({best[j], best[x] + best[x ^ j]});
        }
        // cout << best[j] << endl;
    }

    cout << best[(1 << G) - 1] << endl;
    return 0;
}