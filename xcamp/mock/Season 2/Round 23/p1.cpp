/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <cassert>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 360, MAXM = 50;
int N, M;
int arr[MAXN];
int dp[5][MAXM][MAXM][MAXM][MAXM];
int present[5];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= M; i++)
    {
        int n;
        cin >> n;
        present[n]++;
    }

    dp[0][0][0][0][0] = arr[1];
    for (int i = 1; i < N; i++) 
    {
        // cout << "new index: " << i << endl;
        for (int a = 0; a <= present[1]; a++) for (int b = 0; b <= present[2]; b++) 
        for (int c = 0; c <= present[3]; c++) 
        {
            int d = i - 1 - a - 2 * b - 3 * c;
            if (d % 4) continue;
            d /= 4;
            if (d < 0 || d > present[4]) continue;
            if (!dp[0][a][b][c][d]) continue;
            dp[1][a + 1][b][c][d] = max(dp[1][a + 1][b][c][d], dp[0][a][b][c][d] + arr[i + 1]);
            dp[2][a][b + 1][c][d] = max(dp[2][a][b + 1][c][d], dp[0][a][b][c][d] + arr[i + 2]);
            dp[3][a][b][c + 1][d] = max(dp[3][a][b][c + 1][d], dp[0][a][b][c][d] + arr[i + 3]);
            dp[4][a][b][c][d + 1] = max(dp[4][a][b][c][d + 1], dp[0][a][b][c][d] + arr[i + 4]);
        }

        for (int a = 0; a <= present[1]; a++) for (int b = 0; b <= present[2]; b++) 
        for (int c = 0; c <= present[3]; c++) for (int d = 0; d <= present[4]; d++)
        {
            dp[0][a][b][c][d] = dp[1][a][b][c][d];
            dp[1][a][b][c][d] = dp[2][a][b][c][d];
            dp[2][a][b][c][d] = dp[3][a][b][c][d];
            dp[3][a][b][c][d] = dp[4][a][b][c][d];
        }
    }

    cout << dp[0][present[1]][present[2]][present[3]][present[4]] << endl;
    return 0;
} 