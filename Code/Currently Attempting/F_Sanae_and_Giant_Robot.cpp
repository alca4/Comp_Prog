/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
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
#include <bitset>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
int N, M;

struct ST
{
    pii seg[4 * MAXN];
    int sum[4 * MAXN];
    int lazy[4 * MAXN];

    void apply(int cid)
    {
        seg[cid] = {0, 0};
        sum[cid] = 0;
        lazy[cid] = 1;
    }

    void push(int cid, int ss, int se)
    {
        if (ss < se)
        {
            apply(cid * 2);
            apply(cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, int v, int cid, int ss, int se)
    {
        if (a <= ss && se <= b)
        {
            seg[cid] = {v, v};
            sum[cid] = v;
            if (a != b) lazy[cid] = 1;
            return;
        }

        if (a != b) push(cid, ss, se);

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid].F = max(seg[cid * 2].F, seg[cid * 2 + 1].F);
        seg[cid].S = min(seg[cid * 2].S, seg[cid * 2 + 1].S);
        sum[cid] = sum[cid * 2] + sum[cid * 2 + 1];
    }

    int query(int a, int cid, int ss, int se)
    {
        if (ss == se) return sum[cid];

        int mid = (ss + se) / 2;
        int ans = 0;
        if (a <= mid) ans += query(a, cid * 2, ss, mid);
        else ans += query(a, cid * 2 + 1, mid + 1, se);
        return ans;
    }

    void clear(int cid, int ss, int se)
    {
        seg[cid] = {0, 0};
        lazy[cid] = sum[cid] = 0;

        if (ss == se) return;
        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST seg;
int a[MAXN], b[MAXN];
set<pii> itv;

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];
    for (int i = 1; i <= N; i++) seg.update(i, i, a[i] - b[i], 1, 1, N);

    for (int i = 1; i <= M; i++) 
    {
        int x = read(), y = read();
        if (seg.query(x, y, 1, 1, N) == 0)
        {

        }
    }

    // cout << seg.seg[1].F << " " << seg.seg[1].S << endl;

    for (int i = 1; i <= N; i++) cout << seg.query(i, i, 1, 1, N) << " ";
    cout << endl;

    if (seg.seg[1].F == seg.seg[1].S && seg.seg[1].F == 0 && seg.sum[1] == 0) 
        cout << "YES" << endl;
    else cout << "NO" << endl;
    seg.clear(1, 1, N);
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