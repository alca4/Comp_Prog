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

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 20;
int N;
int vis[1 << MAXN];
vector<int> nbs[1 << MAXN];

int found = 0, ans = 0;
void DFS(int a)
{
    vis[a] = 1;
    found++;
    for (int i = 0; i < nbs[a].size(); i++)
    {
        if (found == (1 << N)) ans = 1;
        if (vis[nbs[a][i]]) continue;
        if (!ans) DFS(nbs[a][i]);
    }
    if (ans) 
    {
        for (int j = 0; j < N; j++) cout << ((a & (1 << j)) > 0);
        cout << endl;
    }
    vis[a] = 0;
    found--;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for (int i = 0; i < (1 << N); i++)
        for (int j = 0; j < N; j++)
            nbs[i].pb(i ^ (1 << j));
    
    DFS(0);
}