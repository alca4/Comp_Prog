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
#define INF 1000000000
#define MOD 1000000007
#define all(x) (x).begin(), (x).end()
#define reset(x) memset(x, 0, sizeof(x))

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

void print(const vector<int>& vec)
{
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
    cout << endl;
}

const int MAXN = 5010, MAXM = 5010;
int N, M;
string s1, s2;
short dp[MAXN][MAXM][3];

void solve()
{
    // cout << "====" << endl;
    cin >> N >> M;
    cin >> s1 >> s2;

    s1 = '#' + s1;
    s2 = '#' + s2;

    for (int i = 0; i <= N; i++) for (int j = 0; j <= M; j++) 
        dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 10000;

    dp[0][0][0] = 1;
    dp[0][0][1] = dp[0][0][2] = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= M; j++)
        {
            if (s1[i] == s2[j])
            {
                dp[i][j][0] = min(dp[i - 1][j - 1][0] + 1, dp[i - 1][j][0] + 2);
                dp[i][j][1] = min(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]);
                dp[i][j][2] = min({dp[i - 1][j][0], dp[i - 1][j][1], 
                                   dp[i - 1][j][2], dp[i - 1][j - 1][2]}) + 1;
            }
            else
            {
                dp[i][j][0] = dp[i - 1][j][0] + 2;
                dp[i][j][2] = min({dp[i - 1][j][0], dp[i - 1][j][1], 
                                   dp[i - 1][j][2]}) + 1;
            }
        }

    int ans = 10000;
    for (int i = 1; i <= N; i++)
        ans = min(ans, min({dp[i][M][0], dp[i][M][1], dp[i][M][2]}) + N - i);
    if (ans != 10000) cout << ans << endl;
    else cout << -1 << endl;
    for (int i = 0; i <= N; i++) for (int j = 0; j <= M; j++) reset(dp[i][j]);
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