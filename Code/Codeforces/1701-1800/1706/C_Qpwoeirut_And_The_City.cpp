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
#define INF 1000000000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

void solve()
{
    int N;
    cin >> N;

    ll arr[MAXN];
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    if (N % 2 == 1)
    {
        ll ans = 0;
        for (int i = 2; i <= N - 1; i += 2)
        {
            if (arr[i] <= arr[i - 1] || arr[i] <= arr[i + 1]) 
                ans += max(arr[i - 1], arr[i + 1]) - arr[i] + 1;
        }
        cout << ans << endl;
    }
    else
    {
        ll pref[MAXN], suff[MAXN];
        pref[0] = suff[(N - 1) / 2 + 1] = 0;
        int pi = 1;
        for (int i = 2; i <= N - 2; i += 2)
        {
            pref[pi] = pref[pi - 1];
            if (arr[i] <= arr[i - 1] || arr[i] <= arr[i + 1])
                pref[pi] += (max(arr[i - 1], arr[i + 1]) - arr[i] + 1);
            pi++;
        }

        // for (int i = 1; i <= (N - 1) / 2; i++) cout << pref[i] << " ";
        // cout << endl;

        int si = (N - 1) / 2;
        for (int i = N - 1; i >= 3; i -= 2)
        {
            suff[si] = suff[si + 1];
            if (arr[i] <= arr[i - 1] || arr[i] <= arr[i + 1]) 
                suff[si] += (max(arr[i - 1], arr[i + 1]) - arr[i] + 1);
            si--;
        }

        // for (int i = 1; i <= (N - 1) / 2; i++) cout << suff[i] << " ";
        // cout << endl;

        ll ans = INF;
        for (int i = 0; i <= (N - 1) / 2; i++)
        {
            ans = min(ans, pref[i] + suff[i + 1]);
        }
        cout << ans << endl;

        for (int i = 1; i <= (N - 1) / 2; i++) pref[i] = suff[i] = 0;
    }
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