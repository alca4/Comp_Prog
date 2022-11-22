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
int pv[MAXN];
int nv[MAXN];
map<int, int> last;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = N; i >= 1; i--)
    {
        if (last.find(arr[i]) == last.end()) nv[i] = INF;
        else nv[i] = last[arr[i]];
        last[arr[i]] = i;
    }
    last.clear();
    for (int i = 1; i <= N; i++)
    {
        if (last.find(arr[i]) == last.end()) pv[i] = -1;
        else pv[i] = last[arr[i]];
        last[arr[i]] = i;
    }

    ll ans = 0;
    ll l = 1, r = 1;
    int dis = 1;
    while (l <= r && r <= N)
    {
        if (dis > K) 
        {
            // cout << l << " " << r << endl;
            ans += r - l;
            if (nv[l] > r) dis--;
            l++;
        }
        if (dis <= K)
        {
            r++;
            if (pv[r] < l) dis++;
        }
    }
    ll n = (r - l + 1);
    ans += n * (n - 1) / 2;
    cout << ans << endl;
    return 0;
}