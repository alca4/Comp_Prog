#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <unordered_set>
#include <bitset>
using namespace std;

#define ld long double

int N, X, S;
ld choose[110];
int prices[110];
ld dp[110][10010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> X;
    for (int i = 1; i <= N; i++) cin >> prices[i];
    for (int i = 1; i <= N; i++) S += prices[i];

    choose[0] = 1.0;
    int up = 1;
    int down = N;
    for (int i = 1; i <= N; i++)
    {
        choose[i] = choose[i - 1] * up / down;
        up++;
        down--;
    }

    dp[0][0] = 1.0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i; j >= 1; j--)
        {
            for (int k = prices[i]; k <= S; k++)
            {
                dp[j][k] += dp[j - 1][k - prices[i]];
            }
        }
    }

    ld ans = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j <= S; j++)
        {
            ans += dp[i][j] * choose[i] *
                   min((ld) X / 2 * ((ld) N / (i) + 1), 
                       (ld) (j) / (ld) (i));
        }
    

    cout << fixed << setprecision(9) << ans << endl;
    return 0;
}