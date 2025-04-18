/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
Start time: 11:10
End time: 11:59

Takeaways:
Be careful when type segtree!
Look if brackets are out of place
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
int N;
int p[MAXN];
int a[MAXN];
int loc[MAXN];
ll cost[MAXN];

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
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = INF;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }
};

ST seg;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> p[i];
        loc[p[i]] = i;
    }
    for (int i = 1; i <= N; i++) cin >> a[i];

    ll ans = INF;
    for (int i = 1; i <= N - 1; i++) seg.update(i, N - 1, a[i], 1, 1, N - 1);
    ans = min(ans, seg.seg[1]);

    for (int i = 1; i <= N; i++)
    {
        seg.update(1, loc[i] - 1, a[loc[i]], 1, 1, N - 1);
        seg.update(loc[i], N - 1, -1 * a[loc[i]], 1, 1, N - 1);
        ans = min(ans, seg.seg[1]);
    }

    cout << ans << endl;
    return 0;
}