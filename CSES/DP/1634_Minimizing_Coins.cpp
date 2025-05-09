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
#define INF 1000000000
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

const int MAXN = 110;
int N, S;
int arr[MAXN];
int dp[1000010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> S;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    sort(range(arr, 1, N));

    dp[0] = 0;
    for (int i = 1; i <= 1000000; i++) dp[i] = INF;
    for (int i = 1; i <= 1000000; i++)
        for (int j = 1; j <= N; j++)
        {
            if (i < arr[j]) continue;
            dp[i] = min(dp[i], dp[i - arr[j]] + 1);
        }
    
    cout << (dp[S] == INF ? -1 : dp[S]) << endl;
    return 0;
}