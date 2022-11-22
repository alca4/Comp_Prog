/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
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

const int MAXN = 110;
int arr[MAXN];
int dp[MAXN][100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N = read();
    for (int i = 1; i <= N; i++) cin >> arr[i];

    set<int> pos;
    dp[0][0] = 1;
    for (int i = 0; i < N; i++) for (int j = 0; j <= 100000; j++)
    {
        if (dp[i][j])
        {
            dp[i + 1][j] = 1;
            if (j + arr[i + 1] <= 100000)
            {
                dp[i + 1][j + arr[i + 1]] = 1;
                pos.insert(j + arr[i + 1]);
            }
        }
    }

    cout << pos.size() << endl;
    for (auto n : pos) cout << n << " ";
    cout << endl;
    return 0;
}