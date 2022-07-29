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
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 30;
int N, M;
ll K;
ll paths[MAXN][MAXN];
int P;
map<ll, int> occ[MAXN][MAXN];
ll ans = 0;

void forwards(int i, int j, ll v, int l)
{
    if (l == P) 
    {
        occ[i][j][v]++;
        return;
    }
    
    if (i < N) forwards(i + 1, j, v ^ paths[i + 1][j], l + 1);
    if (j < M) forwards(i, j + 1, v ^ paths[i][j + 1], l + 1);
}

void backwards(int i, int j, ll v, int l)
{
    if (l == (N + M - 2) - P)
    {
        ans += occ[i][j][v ^ K ^ paths[i][j]];
        return;
    }

    if (i > 1) backwards(i - 1, j, v ^ paths[i - 1][j], l + 1);
    if (j > 1) backwards(i, j - 1, v ^ paths[i][j - 1], l + 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            cin >> paths[i][j];
    
    P = (N + M - 2) / 2;

    forwards(1, 1, paths[1][1], 0);
    backwards(N, M, paths[N][M], 0);

    cout << ans << endl;
    return 0;
}