/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
typedef pair<int, int> pii;

const int MAXN = 50010;
int N, M;
vector<pii> nbs[MAXN];
pii dp[MAXN];

void DP(int a, int p, int m)
{
    multiset<int> paths;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i].FF != p)
    {
        int nb = nbs[a][i].FF;
        ll l = nbs[a][i].SS;
        DP(nb, a, m);
        dp[a].FF += dp[nb].FF;
        paths.insert(dp[nb].SS + l);
    }
    while (paths.size() && *paths.rbegin() >= m)
    {
        dp[a].FF++;
        paths.erase(paths.find(*paths.rbegin()));
    }
    while (paths.size() > 1)
    {
        int x = *paths.begin();
        paths.erase(paths.begin());
        if (paths.lower_bound(m - x) != paths.end() && x + *paths.lower_bound(m - x) >= m)
        {
            paths.erase(paths.lower_bound(m - x));
            dp[a].FF++;
        }
        else dp[a].SS = max(dp[a].SS, x);
    }
    if (paths.size()) dp[a].SS = max(dp[a].SS, *paths.rbegin());
}

int main()
{
    // srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i < N; i++)
    {
        int a, b, l;
        cin >> a >> b >> l;
        nbs[a].pb({b, l});
        nbs[b].pb({a, l});
    }

    int lb = 0;
    int ub = INF;
    int ans = 0;
    while (lb <= ub)
    {
        int mid = (lb + ub) / 2;
        DP(1, 0, mid);
        // cout << mid << " " << dp[1].FF << endl;

        if (dp[1].FF >= M) 
        {
            // cout << mid << " works " << endl;
            ans = mid;
            lb = mid + 1;
        }
        else ub = mid - 1;

        for (int i = 1; i <= N; i++) dp[i] = {0, 0};
    }
    
    cout << ans << endl;
    return 0;
} 