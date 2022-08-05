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
vector<int> nbs[MAXN];
int indeg[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a = read(), b = read();
        nbs[a].pb(b);
        indeg[b]++;
    }

    set<pii> indegs;
    for (int i = 1; i <= N; i++) indegs.insert({indeg[i], i});
    queue<int> vals;
    for (int i = 1; i <= N; i++)
    {
        if (indegs.begin()->FF != 0)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        int a = indegs.begin()->SS;
        indegs.erase(indegs.begin());
        vals.push(a);
        for (int j = 0; j < nbs[a].size(); j++)
        {
            int tar = nbs[a][j];
            indegs.erase({indeg[tar], tar});
            indeg[tar]--;
            indegs.insert({indeg[tar], tar});
        }
    }

    while (!vals.empty()) 
    {
        int a = vals.front();
        cout << a << " ";
        vals.pop();
    }
    cout << endl;
    return 0;
}