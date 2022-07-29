#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

#define ll long long
#define INF 1000000000ull
ll D = 1000000;

int N, M;
int a[500010];
int b[500010];
int range[500010];
ll dp[500010];
vector<ll> seg;
vector<int> lc;
vector<int> rc;

int create()
{
    seg.push_back(INF);
    lc.push_back(-1);
    rc.push_back(-1);
    return seg.size() - 1;
}

int update(ll a, ll v, int cid, ll ss, ll se)
{
    if (cid == -1) cid = create();
    if (ss == se) 
    {
        seg[cid] = v;
        return cid;
    }

    ll mid = (ss + se) / 2;
    if (a <= mid) lc[cid] = update(a, v, lc[cid], ss, mid);
    else rc[cid] = update(a, v, rc[cid], mid + 1, se);
    
    ll ans = INF;
    if (lc[cid] != -1) ans = min(ans, seg[lc[cid]]);
    if (rc[cid] != -1) ans = min(ans, seg[rc[cid]]);
    seg[cid] = ans;
    return cid;
}

ll query(ll a, ll b, int cid, ll ss, ll se)
{
    if (cid == -1) return INF;
    if (a <= ss && se <= b) return seg[cid];

    ll mid = (ss + se) / 2;
    ll ans = INF;
    if (a <= mid) ans = min(ans, query(a, b, lc[cid], ss, mid));
    if (b > mid) ans = min(ans, query(a, b, rc[cid], mid + 1, se));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= M; i++) cin >> b[i];
    sort(b + 1, b + M + 1);
    a[0] = 0;
    a[N + 1] = INF;

    for (int i = 1; i <= N; i++)
    {
        range[i] = distance(b + 1, lower_bound(b + 1, b + M + 1, a[i]));
    }
    range[0] = 0;
    range[N + 1] = M;

    create();
    dp[N + 1] = 0;

    for (int i = N; i >= 0; i--)
    {
        dp[i] = query(range[i] - i - 1 + D, INF, 0, 1, INF);
        if (dp[i] < INF) dp[i] -= (i + 1);
        if (a[i + 1] > a[i]) dp[i] = min(dp[i], dp[i + 1]);
        update(range[i + 1] - (i + 1) + D, dp[i + 1] + i + 1, 0, 1, INF);
    }

    ll ans = dp[0];
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}