#include<iostream>
#include<cmath>
#include<vector>
#include<bitset>
#include<algorithm>
using namespace std;

#define ll long long

int N, M;
int adjmat[20][20];
ll dp[1 << 20][20];

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adjmat[a - 1][b - 1] = 1;
        adjmat[b - 1][a - 1] = 1;
    }

    for (int i = 0; i < N; i++) dp[1 << i][i] = 1;
    ll ans = 0;
    for (int i = 1; i < (1 << N); i++)
    {
        int init = log2(i & -i);
        for (int j = 0; j < N; j++)
        {
            if ((i | (1 << j)) != i) continue;
            for (int k = init; k < N; k++)
            {
                if (!adjmat[j][k]) continue;
                if (k == init && ((1 << j) | (1 << k)) != i)
                    ans += dp[i][j];
                if ((i | (1 << k)) != i)
                    dp[i | (1 << k)][k] += dp[i][j];
            }
        }
    }
    cout << ans / 2 << endl;
    return 0;
}