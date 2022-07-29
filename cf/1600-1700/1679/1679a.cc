#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T, N;

void solve()
{
    long long a;
    cin >> a;
    if (a % 2 != 0 || a < 4)
    {
        cout << -1 << endl;
        return;
    }
    a /= 2;
    if (a % 3 == 0)
    {
        cout << a / 3 << " ";
    }
    else
    {
        cout << a / 3 + 1 << " ";
    }
    cout << a / 2 << endl;
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