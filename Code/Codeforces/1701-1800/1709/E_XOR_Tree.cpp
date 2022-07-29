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

const int MAXN = 200010;
int N;
vector<int> nbs[MAXN];
set<int> stl[MAXN];
int arr[MAXN];
int b[MAXN];
int ans = 0;

void combine(int a, int b, int v)
{
    if (stl[b].size() > stl[a].size()) stl[a].swap(stl[b]);
    for (auto n : stl[b]) 
    {
        if (stl[a].find(n ^ v) != stl[a].end())
        {
            ans++;
            stl[b].clear();
            stl[a].clear();
            return;
        }
        stl[a].insert(n);
    }
    stl[b].clear();
}

void DFS(int a, int p)
{
    b[a] = b[p] ^ arr[a];
    stl[a].insert(b[a]);

    bool bad = 0;
    for (int i = 0; i < nbs[a].size(); i++)
    {
        int b = nbs[a][i];
        if (b == p) continue;
        DFS(b, a);

        if (stl[a].size() < stl[b].size()) stl[a].swap(stl[b]);
        for (auto n : stl[b])
            if (stl[a].find(n ^ arr[a]) != stl[a].end()) bad = 1;
        for (auto n : stl[b]) stl[a].insert(n);
        stl[b].clear();
    }
    if (bad)
    {
        stl[a].clear();
        ans++;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i < N; i++)
    {
        int a = read();
        int b = read();
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);
    cout << ans << endl;
    return 0;
}