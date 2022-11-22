/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ull
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

const int MAXN = 500010;
vector<pll> nbs[MAXN];
int pv[MAXN];
ll dist[MAXN];
int vis[MAXN];
int inq[MAXN];
int N, M;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        ll a = read(), b = read(), c = read();
        nbs[a].pb({b, c});
    }

    for (int i = 1; i <= N; i++) dist[i] = INF;

    int cycle = 0;
    for (int i = 1; i <= N; i++) if (vis[i] == 0)
    {
        queue<int> search;
        dist[i] = 0;
        search.push(i);
        inq[i] = 1;
        while (!search.empty())
        {
            int n = search.front();
            // cout << n << endl;
            inq[n] = 0;
            search.pop();

            for (int i = 0; i < nbs[n].size(); i++)
            {
                int tar = nbs[n][i].FF;
                // cout << "to " << tar << endl;
                ll w = nbs[n][i].SS;

                if (dist[tar] > dist[n] + w)
                {
                    dist[tar] = dist[n] + w;
                    pv[tar] = n;
                    if (!inq[tar])
                    {
                        inq[tar] = 1;
                        search.push(tar);
                        vis[tar]++;
                        if (vis[tar] == N)
                        {
                            cycle = tar;
                            break;
                        }
                    }
                }
            }
            if (cycle != 0) break;
            // reset(vis);
        }
        if (cycle != 0) break;
    }

    if (cycle == 0)
    {
        cout << "NO" << endl;
        return 0;
    }
    
    cout << "YES" << endl;
    stack<int> a;
    set<int> vals;
    a.push(cycle);
    vals.insert(cycle);
    int tmp = pv[cycle];
    while (vals.find(tmp) == vals.end()) 
    {
        a.push(tmp);
        vals.insert(tmp);
        tmp = pv[tmp];
    }
    a.push(tmp);

    cout << a.top() << " ";
    a.pop();
    while (!a.empty() && a.top() != tmp)
    {
        cout << a.top() << " ";
        a.pop();
    }
    cout << tmp << endl;
    return 0;
}