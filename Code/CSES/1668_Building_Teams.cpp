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

const int MAXN = 500010;
int N, M;
vector<int> nbs[MAXN];
int col[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a = read(), b = read();
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++)
    {
        if (col[i] != 0) continue;
        queue<int> q;
        q.push(i);
        col[i] = 1;
        while (!q.empty())
        {
            int a = q.front();
            q.pop();

            for (int i = 0; i < nbs[a].size(); i++)
            {
                if (!col[nbs[a][i]])
                {
                    col[nbs[a][i]] = 3 - col[a];
                    q.push(nbs[a][i]);
                }
                if (col[nbs[a][i]] == col[a])
                {
                    cout << "IMPOSSIBLE" << endl;
                    return 0;
                }
            }
        }
    }

    for (int i = 1; i <= N; i++) cout << col[i] << " ";
    cout << endl;
    return 0;
}