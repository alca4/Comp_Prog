/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet hard carrying
Start time:
End time:
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
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 100000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 3010;
ll arr[MAXN];
ll p[MAXN];

void solve()
{
    ll N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; i++) cin >> arr[i];

    sort(arr + 1, arr + N + 1);

    ll ans = INF;
    for (int i = 1; i <= arr[N]; i++)
    {
        if (i > arr[1]) break;
        for (int j = 1; j <= N; j++) p[j] = min(K, arr[j] / i);
        ll mval = 0;
        for (int j = 1; j <= N; j++) mval = max(mval, arr[j] / p[j]);
        ans = min(ans, mval - i);
    }

    cout << ans << endl;
    for (int i =1; i <= N; i++) arr[i] = p[i] = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}