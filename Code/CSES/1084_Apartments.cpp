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

const int MAXN = 200010;
int N, M, K;
int apart[MAXN];
int app[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) cin >> apart[i];
    sort(range(apart, 1, N));
    for (int i = 1; i <= M; i++) cin >> app[i];
    sort(range(app, 1, M));
    
    int i = 1, j = 1, ans = 0;
    while (i <= N && j <= M)
    {
        if (abs(apart[i] - app[j]) <= K) ans++, i++, j++;
        else if (apart[i] > app[j]) j++;
        else i++;
    }
    cout << ans << endl;
    return 0;
}