/*
Idea: dp and segtree
dp[i] = max score with first i roads and ith road is fixed
dp[i] = max(dp[j] + {races contained in [j, i]} - c_j - c_j+1 - c_j+2...)
use RURQ segtree for races: when at i, loop races
for race that starts at j increase 1 to j - 1 by profit from that race
use psums for cost of roads
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 200010;
int N, M;
ll cost[MAXN];
ll dp[MAXN];
vector<pll> races[MAXN];

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

    void apply(ll v, int cid)
    {
        lazy[cid] += v;
        seg[cid] += v;
    }

    void push(int cid, int ss, int se)
    {
        if (ss != se)
        {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, ll v, int cid, int ss, int se)
    {
        if (a > b) return;
        if (a <= ss && se <= b)
        {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a > b) return 0;
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = -INF;
        if (a <= mid) ans = max(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = max(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    N++;
    for (int i = 2; i <= N; i++) cin >> cost[i];
    for (int i = 2; i <= N; i++) cost[i] += cost[i - 1];

    for (int i = 1; i <= M; i++)
    {
        ll a, b, v;
        cin >> a >> b >> v;
        races[++b].pb(pll(++a, v));
    }

    for (int i = 2; i <= N; i++)
    {
        for (int j = 0; j < races[i].size(); j++)
            st.update(1, races[i][j].FF - 1, races[i][j].SS, 1, 1, N);
        dp[i] = max(dp[i - 1], st.query(1, i - 1, 1, 1, N) - cost[i]);
        st.update(i, i, dp[i] + cost[i], 1, 1, N);
    }
    // for (int i = 2; i <= N; i++) cout << dp[i] << endl;
    cout << dp[N] << endl;
    return 0;
}