/*
Learnings:

Write simple code!
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int T, N;
int a[100010];
int b[100010];
int nbs[100010];
int vis[100010];
vector<int> cycles;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--)
    {
        for (int i = 1; i <= N; i++) a[i] = b[i] = nbs[i] = vis[i] = 0;
        cycles.resize(0);

        cin >> N;
        for (int i = 1; i <= N; i++) cin >> a[i];
        for (int i = 1; i <= N; i++) cin >> b[i];

        for (int i = 1; i <= N; i++) nbs[a[i]] = b[i];

        for (int i = 1; i <= N; i++)
        {
            if (vis[i]) continue;
            int sz = 0;
            int tmp = i;
            while (!vis[tmp])
            {
                vis[tmp] = 1;
                sz++;
                tmp = nbs[tmp];
            }
            cycles.push_back(sz);
        }

        sort(cycles.begin(), cycles.end());
        
        long long ans = 0;
        for (int i = 0; i < cycles.size(); i++) ans += (cycles[i] / 2);
        cout << ans * (N - ans) * 2 << endl;
    }
    return 0;
}