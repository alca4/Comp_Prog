#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void solve()
{
    int A, B;
    cin >> A >> B;
    string str;
    while (A > 0 && B > 0)
    {
        str += "01";
        A--;
        B--;
    }
    if (A > 0) for (int i = 0; i < A; i++) str += "0";
    if (B > 0) for (int i = 0; i < B; i++) str += "1";
    cout << str << endl;
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