#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

#define ll long long

void solve()
{
    int N;
    cin >> N;
    string a[200010];
    unordered_map<char, int> l1;
    for (int i = 1; i <= 2 * N + 1; i++) 
    {
        cin >> a[i];
        for (int j = 0; j < a[i].length(); j++)
            l1[a[i][j]]++;
    }
    for (auto n : l1)
    {
        if (n.second % 2 != 0) cout << n.first << endl;
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