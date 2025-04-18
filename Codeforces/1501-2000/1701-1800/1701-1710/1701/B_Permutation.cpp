#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

void solve()
{
    int N;
    cin >> N;

    cout << 2 << endl;
    set<int> vals;
    for (int i = 1; i <= N; i++)
    {
        for (int j = i; j <= N; j *= 2)
        {
            if (vals.find(j) != vals.end()) break;
            cout << j << " ";
            vals.insert(j);
        }
    }
    cout << endl;
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