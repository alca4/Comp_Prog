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
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007
#define reset(x) memset(x, 0, sizeof(x))
#define print(a, x, y) {for (int i = x; i <= y; i++) cout << a[i] << " "; cout << endl;}

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
int N, K;
int arr[MAXN];
int m[MAXN];

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    sort(arr + 1, arr + 1 + N);
    for (int i = 1; i <= N; i++)
    {
        int pv = INF;
        for (int j = 1; j <= min(arr[i], K); j = arr[i] / (arr[i] / j) + 1)
        {
            int nv = arr[i] / j;
            m[nv + 1] = max(m[nv + 1], pv);
            pv = nv;
        }

        m[0] = max(m[0], pv);
    }

    // print(m, 1, N);

    int ans = INF;
    int mval = 0;
    for (int i = 0; i <= arr[1]; i++)
    {
        mval = max(mval, m[i]);
        ans = min(ans, mval - i);
    }

    cout << ans << endl;

    reset(m);
    reset(arr);
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