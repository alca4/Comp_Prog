#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve()
{
    int N;
    cin >> N;

    int arr[200010];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    long long sum = 0;
    for (int i = 1; i <= N; i++)
    {
        sum += arr[i];
        if (sum < 0)
        {
            cout << "NO" << endl;
            return;
        }
        if (sum == 0)
        {
            for (int j = i + 1; j <= N; j++)
                if (arr[j] != 0) 
                {
                    cout << "NO" << endl;
                    return;
                }
        }
    }
    if (sum != 0) cout << "NO" << endl;
    else cout << "YES" << endl;
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