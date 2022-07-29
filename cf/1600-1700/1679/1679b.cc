#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long

int T, N, Q;
ll arr[200010];
ll last[200010];

void solve()
{
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    ll sum = 0;
    for (int i = 1; i <= N; i++) sum += arr[i];
    ll val = 0;
    int id = -1;
    for (int i = 1; i <= Q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int j, v;
            cin >> j >> v;
            if (last[j] < id) sum -= val;
            else sum -= arr[j];
            arr[j] = v;
            sum += v;
            last[j] = i;
        }
        else
        {
            int v;
            cin >> v;
            id = i;
            val = v;
            sum = N * val;
        }
        cout << sum << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    T = 1;
    while (T--) solve();
    return 0;
}