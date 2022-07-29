#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T, N, M;
int grid[200010][2];
int dp[200010][4];

int DP(int col, int fill)
{
    int ans = 0;
    if (dp[col][fill] != 0) return dp[col][fill];
    if (col == M)
    {
        if (fill == 1 || fill == 2) return 0;
        if (fill == 3) return 1;
    }
    if (fill == 0)
    {
        ans = DP(col + 1, grid[col + 1][0] + 2 * grid[col + 1][1]);
    }
    if (fill == 1)
    {
        ans = DP(col + 1, 1 + 2 * grid[col + 1][1]) + 1;
    }
    if (fill == 2)
    {
        ans = DP(col + 1, grid[col + 1][0] + 2) + 1;
    }
    if (fill == 3)
    {
        ans = min(DP(col, 1), DP(col, 2)) + 1;
    }
    dp[col][fill] = ans;
    return ans;
}

void solve()
{
    cin >> N;
    string str;
    cin >> str;
    for (int i = 1; i <= N; i++) 
    {
        grid[i][0] = (str[i - 1] == '*' ? 1 : 0);
        if (grid[i][0] == 1) M = max(M, i);
    }
    cin >> str;
    for (int i = 1; i <= N; i++) 
    {
        grid[i][1] = (str[i - 1] == '*' ? 1 : 0);
        if (grid[i][1] == 1) M = max(M, i);
    }
    //cout << "last filled colum is: " << M << endl;
    int fill = grid[1][0] + 2 * grid[1][1];
    cout << DP(1, fill) << endl;

    for (int i = 1; i <= N; i++)
    {
        grid[i][0] = grid[i][1] = 0;
        for (int j = 0; j < 4; j++) dp[i][j] = 0;
    }
    M = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--) solve();
    return 0;
}