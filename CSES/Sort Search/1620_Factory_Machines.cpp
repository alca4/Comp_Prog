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

const int MAXN = 200010;
int N, T;
ll arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> T;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    sort(range(arr, 1, N));

    ll lb = 1;
    ll ub = INF;
    ll ans = INF;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;

        ll tot = 0;
        for (int i = 1; i <= N; i++) 
        {
            tot += mid / arr[i];
            if (tot >= T) break;
        }

        if (tot >= T)
        {
            ans = min(ans, mid);
            ub = mid - 1;
        }
        else lb = mid + 1;
    }

    cout << ans << endl;
    return 0;
}