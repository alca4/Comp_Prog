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
#define INF 1000000000
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
    int N, M;
    cin >> N >> M;

    int arr[MAXN];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    string str;
    for (int i = 1; i <= M; i++) str += "B";

    for (int i = 1; i <= N; i++)
    {
        int c1 = arr[i];
        int c2 = M + 1 - arr[i];
        int f = min(c1, c2);
        int s = max(c1, c2);
        if (str[f - 1] != 'A') str[f - 1] = 'A';
        else if (str[s - 1] != 'A') str[s - 1] = 'A';
    }

    cout << str << endl;
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