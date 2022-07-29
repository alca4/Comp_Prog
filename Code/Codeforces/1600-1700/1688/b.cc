#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
 
void solve()
{
    int N;
    int a[200010];
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    int needed = 0;
    a[0] = 1;
    int num_odd = 0;
    for (int i = 1; i <= N; i++)
    {
        if (a[i] % 2 == 0) needed++;
        else num_odd++;
    }
    if (num_odd > 0) cout << needed << endl;
    else
    {
        int ans = 1e9;
        for (int i = 1; i <= N; i++)
        {
            int temp = 0;
            while (a[i] % 2 == 0)
            {
                a[i] /= 2;
                temp++;
            }
            ans = min(ans, temp);
        }
        cout << ans + N - 1 << endl;
    }
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