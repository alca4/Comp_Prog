/*
Idea: sqrt
if k < sqrt, then calculate it & save answer
if k > sqrt, just calculate
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, Q;
int arr[100010];
int memo[100010][350];

int DP(int p, int k)
{
    if (p > N) return 0;
    if (memo[p][k]) return memo[p][k];
    int ans = DP(p + arr[p] + k, k) + 1;
    memo[p][k] = ans;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    cin >> Q;
    while (Q--)
    {
        int p, k;
        cin >> p >> k;
        if (k <= 320)
        {
            cout << DP(p, k) << endl;
        }
        else
        {
            int cnt = 0;
            while (p <= N) 
            {
                p += arr[p] + k;
                cnt++;
            }
            cout << cnt << endl;
        }
    }
}