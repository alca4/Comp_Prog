#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int T, N;
int arr[3010];

void solve()
{
    int N;
    string str;
    cin >> str;
    N = str.length();
    str = " " + str + " ";
    int pref[200010];
    int suf[200010];

    for (int i = 1; i <= N; i++) pref[i - 1] = pref[i] + (str[i] == '0' ? -1 : 1);
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