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

void solve()
{
    // cout << "===========" << endl;
    ll x, y;
    cin >> x >> y;
    ll ans;
    ll p = max(x, y) - 1;
    ans = p * p + p + 1;
    if ((max(x, y)) % 2 == 0)
    {
        if (x < y) ans -= (y - x);
        else ans += (x - y);
    }
    else
    {
        if (x < y) ans += (y - x);
        else ans -= (x - y);
    }
    cout << ans << endl;
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