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

const int MAXN = 100010;
int attack[10][10];
int res[10][10];
int ans = 0;

void fill(int i, int j, int v)
{
    for (int k = 1; k <= 8; k++) attack[i][k] += v;
    for (int k = 1; k <= 8; k++) attack[k][j] += v;

    int ti = i, tj = j;
    while (ti >= 1 && tj >= 1) attack[ti--][tj--] += v;
    ti = i, tj = j;
    while (ti <= 8 && tj <= 8) attack[ti++][tj++] += v;
    ti = i, tj = j;
    while (ti >= 1 && tj <= 8) attack[ti--][tj++] += v;
    ti = i, tj = j;
    while (ti <= 8 && tj >= 1) attack[ti++][tj--] += v;
}

void solve(int i)
{
    if (i == 9)
    {
        ans++;
        return;
    }

    for (int j = 1; j <= 8; j++) if (!attack[i][j] && !res[i][j])
    {
        fill(i, j, 1);
        solve(i + 1);
        fill(i, j, -1);
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i <= 8; i++) for (int j = 1; j <= 8; j++)
    {
        char c;
        cin >> c;
        if (c == '*') res[i][j] = 1;
    }

    solve(1);
    cout << ans << endl;
    return 0;
}