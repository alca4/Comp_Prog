#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void solve()
{
    int N;
    cin >> N;
    if (N == 1) cout << 3 << endl;
    else if ((N & -N) == N) cout << N + 1 << endl;
    else cout << (N & -N) << endl;
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