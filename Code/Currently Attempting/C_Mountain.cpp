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
#include <iomanip>
using namespace std;

typedef pair<int, int> pii;
#define F first
#define S second
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007

const int MAXN = 210;

int N, W, H;
int h[MAXN];
struct ST
{
    struct Node
    {
        ld v;
        bool l;
        bool o = 0;
    } seg[40010];

    void apply(int v, int cid)
    {
        seg[cid].l = seg[cid].o = v;
    }

    void push(int cid, int ss, int se)
    {
        if (ss != se)
        {
            apply(seg[cid].l, cid * 2);
            apply(seg[cid].l, cid * 2 + 1);
        }
        seg[cid].l = 0;
    }

    void update(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b)
        {
            apply(1, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, cid * 2, ss, mid);
        if (b > mid) update(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid].l = seg[cid * 2].l && seg[cid * 2 + 1].l;
    }

    void update(int a, ld v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid].v = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid].v = seg[cid * 2].v + seg[cid * 2 + 1].v;
    }

    ld query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b && seg[cid].o) return seg[cid].v;

        int mid = (ss + se) / 2;
        ld ans = 0;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    }
} grid[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> W >> H;
    for (int i = 1; i <= N; i++) cin >> h[i];
    h[0] = h[N + 1] = 0;

    for (int i = 1; i <= N + 1; i++)
    {
        int l = min(h[i], h[i - 1]);
        int u = max(h[i], h[i - 1]);

        for (int j = 1; j <= l; j++) 
        {
            grid[i].update(j, (ld) 1.0, 1, 1, H);
        }

        ld d = 0.5 / (u - l);
        ld ans = 1.0 + d;
        for (int j = l; j < u; j++)
        {
            ans -= 2 * d;
            grid[i].update(j + 1, ans, 1, 1, H);
        }
    }

    DP(0, 0, 0);

    return 0;
}