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
#define INF 100000000000000000ull
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
int N;
ll arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    ll tot_sum = 0;
    for (int i = 0; i < N; i++) 
    {
        cin >> arr[i];
        tot_sum += arr[i];
    }

    ll best = INF;

    for (int j = 0; j < (1 << N); j++)
    {
        ll sum = 0;
        for (int i = 0; i < N; i++) if ((j & (1 << i)) > 0)
            sum += arr[i];
        best = min(best, abs(sum - tot_sum + sum));
    }
    cout << best << endl;
    return 0;
}