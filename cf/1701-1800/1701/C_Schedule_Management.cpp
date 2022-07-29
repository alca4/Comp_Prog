#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define ll long long

void solve()
{
    int N, M;
    cin >> N >> M;

    ll prof[200010];
    for (int i = 1; i <= N; i++) prof[i] = 0;
    for (int i = 1; i <= M; i++) 
    {
        int n;
        cin >> n;
        prof[n]++;
    }

    sort(prof + 1, prof + 1 + N);

    ll lb = 1;
    ll ub = 2 * M;
    ll best = 1000000000;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;

        int help = (lower_bound(prof + 1, prof + 1 + N, mid) - prof);
        if (help > N)
        {
            best = min(best, mid);
            ub = mid - 1;
        }
        ll extra = 0;
        for (int i = help; i <= N; i++) extra += (prof[i] - mid);
        for (int i = 1; i < help; i++) extra -= (mid - prof[i]) / 2;

        if (extra <= 0) 
        {
            best = min(best, mid);
            ub = mid - 1;
        }
        else
        {
            lb = mid + 1;
        }
    }
    cout << best << endl;
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