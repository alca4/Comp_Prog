#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long

int N;
ll arr[100010];
map<ll, int> vals;
ll ans[100010];

bool works(int l, int r)
{
    if (l == r) return 1;
    if ((arr[r] - arr[l - 1]) % 2 != 0) return 0;

    ll v = (arr[r] - arr[l - 1]) / 2;
    if (vals.find(v + arr[l - 1]) != vals.end())
    {
        int id = vals[v + arr[l - 1]];
        return works(l, id) && works(id + 1, r);
    }
    else return 0;
}

void solve()
{
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) arr[i] += arr[i - 1];
    for (int i = 1; i <= N; i++) vals[arr[i]] = i;

    if (works(1, N)) cout << "Yes" << endl;
    else cout << "No" << endl;
    for (int i = 1; i <= N; i++) arr[i] = 0;
    vals.clear();
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