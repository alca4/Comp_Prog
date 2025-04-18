#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve()
{
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a + b + c + d == 4) cout << 2 << endl;
    else if (a + b + c + d == 0) cout << 0 << endl;
    else cout << 1 << endl;
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