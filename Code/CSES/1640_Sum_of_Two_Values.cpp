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
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
map<int, vector<int>> v;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, X;
    cin >> N >> X;
    for (int i = 1; i <= N; i++) v[read()].pb(i);

    for (auto n : v) if (v.find(X - n.first) != v.end())
    {
        if (n.first * 2 == X && n.second.size() == 1) continue;
        cout << n.S[0] << " " << v[X - n.first][v[X - n.first].size() - 1] << endl;
        return 0;
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}