#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;
 
int T, N;
 
void solve()
{
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    if (l1 <= l2 && l2 <= r1) cout << l2 << endl;
    else if (l2 <= l1 && l1 <= r2) cout << l1 << endl;
    else cout << l1 + l2 << endl;
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