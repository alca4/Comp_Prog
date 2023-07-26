#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long

void solve()
{
    ll N, K;
    ll a[200010];
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];

    int tmp = min(N, K);
    ll max_sum = 0;
    for (int i = 1; i <= tmp; i++) max_sum += a[i];
    ll cur_sum = max_sum;
    for (int i = tmp + 1; i <= N; i++)
    {
        cur_sum += (a[i] - a[i - tmp]);
        max_sum = max(max_sum, cur_sum);
    }
    
    if (K > N) max_sum += (N * K) - (N * (N + 1) / 2);
    else max_sum += (K * (K - 1)) / 2;
    cout << max_sum << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}