#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MOD 1000000007
#define ll long long

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) 
    {
        int N;
        ll arr[100010];
        ll dp[100010];
        cin >> N;

        dp[1] = 1;
        for (int i = 1; i <= N; i++)
        {
            cin >> arr[i];
            if (arr[i] < i - 1 || arr[i] > N - 1) dp[1] = 0;
        }

        if (arr[1] != 0 || arr[N] != N - 1) dp[1] = 0;

        for (int i = 2; i <= N; i++)
        {
            if (arr[i] < arr[i - 1]) dp[i] = 0;
            if (arr[i] > arr[i - 1]) dp[i] = dp[i - 1] * 2;
            if (arr[i] == arr[i - 1]) dp[i] = dp[i - 1] * (arr[i] - i + 2);
            dp[i] %= MOD;
        }
        cout << dp[N] << endl;
    }
    return 0;
}