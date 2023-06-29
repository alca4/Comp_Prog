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

const int MAXN = 5010;
string s, t;
int dp[MAXN][MAXN];

int DP(int i, int j)
{
    if (i == s.length() && j == t.length()) return 0;
    if (i == s.length()) return t.length() - j;
    if (j == t.length()) return s.length() - i;
    if (dp[i][j] >= 0) return dp[i][j];

    int o1, o2, o3;

    o1 = DP(i, j + 1) + 1;
    o2 = DP(i + 1, j) + 1;
    o3 = DP(i + 1, j + 1);
    if (s[i] != t[j]) o3++;

    return dp[i][j] = min({o1, o2, o3});
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> s >> t;
    s = '#' + s;
    t = '#' + t;

    for (int i = 1; i < s.length(); i++) for (int j = 1; j < t.length(); j++) dp[i][j] = -1;

    cout << DP(1, 1) << endl;
    return 0;
}