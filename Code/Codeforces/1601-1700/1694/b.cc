#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve()
{
    int N;
    cin >> N;
    string str;
    cin >> str;

    int arr[200010];
    for (int i = 1; i <= N; i++) arr[i] = str[i - 1] - '0';

    long long ans = N;
    //cout << ans << endl;
    for (int i = N; i >= 2; i--)
    {
        if (arr[i] != arr[i - 1]) ans += i - 1;
    }
    cout << ans << endl;
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