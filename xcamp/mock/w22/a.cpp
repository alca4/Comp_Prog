#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long
#define INF 1000000000000

void solve()
{
    int N;
    ll M;
    ll arr[100010];

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll lb = 1;
    ll ub = INF;
    ll ans = 0;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;
        //cout << lb << " " << mid << " " << ub << endl;

        ll temp[100010];
        for (int i = 1; i <= N; i++)
        {
            temp[i] = mid / arr[i];
            if (temp[i] * arr[i] < mid) temp[i]++;
        }

        ll storage = 0;
        for (int i = 1; i <= N - 1; i++)
        {
            if (temp[i] >= temp[i + 1]) 
            {
                storage += temp[i] * 2;
                if (i == N - 1 && temp[i] > temp[i + 1]) storage--;
                temp[i] = 0;
                temp[i + 1] = 0;
                i++;
            }
            else if (temp[i] < temp[i + 1])
            {
                storage += temp[i] * 2 - 1;
                temp[i + 1] -= (temp[i] - 1);
                temp[i] = 0;
            }
        }
        
        if (temp[N] > 0) storage += temp[N] * 2 - 1;
        
        if (storage <= M) 
        {
            ans = max(ans, mid);
            lb = mid + 1;
        }
        else ub = mid - 1;
    }
    cout << ans << endl;
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