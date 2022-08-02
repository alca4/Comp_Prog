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
#define INF 1000000000000000000ll
#define MOD 1000000007ll
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
ll arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll lb = 1;
    ll ub = INF;
    ll ans = INF;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;
        // cout << mid << endl;

        ll split = 1;
        ll cursum = 0;
        for (int i = 1; i <= N; i++)
        {
            if (arr[i] > mid)
            {
                split = 1000000000;
                break;
            }
            if (cursum + arr[i] > mid)
            {
                cursum = 0;
                split++;
                // cout << "split" << endl;
            }
            cursum += arr[i];
            // cout << cursum << " ";
        }
        // cout << endl;
        // split++;
        // cout << split << endl;

        if (split <= K) 
        {
            ub = mid - 1;
            ans = min(ans, mid);
        }
        if (split > K) lb = mid + 1;
    }
    cout << ans << endl;
    return 0;
}