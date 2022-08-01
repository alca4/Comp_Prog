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

const int MAXN = 30;
ll divs[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    divs[0] = 0;
    for (int i = 1; i <= 16; i++) 
    {
        ll x = pow(10, i - 1);
        divs[i] = i * 9 * x + divs[i - 1];
        // cout << divs[i] << endl;
    }
    // for (int i = 1; i <= 18; i++) cout << divs[i] << endl;

    int Q;
    cin >> Q;
    while (Q--)
    {
        // cout << "===" << endl;
        ll k;
        cin >> k;
        // cout << k << endl;

        auto it = lower_bound(divs, divs + 17, k);
        ll n = distance(divs, it);

        ll dist = (k - divs[n - 1] - 1);
        // cout << dist << endl;
        ll x = 1;
        for (int i = 1; i <= n - 1; i++) x *= 10;
        ll val = dist / n + x;
        // cout << "val is: " << val << endl;
        ll dig = dist - dist / n * n;
        // cout << val * n << " " << dig << endl;
        // cout << "dig is: " << dig << endl;

        // cout << x << endl;
        string str = to_string(val);
        // cout << val + pow(10, n - 1) << endl;
        cout << str[dig] << endl;
    }
    return 0;
}