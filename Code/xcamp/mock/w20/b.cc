#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long
#define MOD 998244353

int N, D;
int arr[510];
ll dp[510][(1 << 11) + 10];

int DP(int id, int mask)
{
    if (dp[id][mask] != -1) return dp[id][mask];
    if (id > D && mask < (1 << (2 * D)) && arr[id] != id - D && arr[id] != -1) 
    {
        dp[id][mask] = 0;
        return 0;
    }
    if (id == N + 1)
    {
        mask = mask >> (D + 1);
        if (mask == (1 << D) - 1) return 1;
        return 0;
    }

    ll ans = 0;
    int lb = max(id - D, 1);
    int ub = min(id + D, N);
    if (arr[id] == -1)
    {
        for (int i = lb; i <= ub; i++)
        {
            if (mask & (1 << (id + D - i))) continue;
            int newmask = (mask | (1 << (id + D - i))) << 1;
            if (newmask >= (1 << (2 * D + 1))) newmask -= (1 << (2 * D + 1));
            ans += DP(id + 1, newmask);
            ans %= MOD;
        }
    }
    else
    {
        if (abs(arr[id] - id) > D) return dp[id][mask] = 0;
        if (mask & (1 << (id + D - arr[id]))) return dp[id][mask] = 0;
        int newmask = (mask | (1 << (id + D - arr[id]))) << 1;
        if (newmask >= (1 << (2 * D + 1))) newmask -= (1 << (2 * D + 1));
        ans = DP(id + 1, newmask);
    }
    return dp[id][mask] = ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> D;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N + 1; i++)
        for (int j = 0; j < (1 << 11); j++)
            dp[i][j] = -1;
    cout << DP(1, 0) << endl;
    return 0;
}