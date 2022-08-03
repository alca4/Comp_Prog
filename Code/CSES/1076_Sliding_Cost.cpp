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

const int MAXN = 500010;
int N, K;
int arr[MAXN];
multimap<int, int> vals;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= K; i++) vals.insert({arr[i], 0});
    auto it = vals.begin();
    ll cost = 0;
    for (int i = 1; i <= K; i++) cost += abs(arr[i] - it->F);
    for (int i = 2; i <= K; i++)
    {
        auto p = it;
        it++;
        ll tmp = cost + (2 * (i - 1) - N) * abs(p->F - it->F);
        cost = min(tmp, cost);
    }
    cout << cost << endl;

    return 0;
}