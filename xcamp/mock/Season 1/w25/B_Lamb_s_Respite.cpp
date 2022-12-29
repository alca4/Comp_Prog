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
#define INF 1000000000
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll readInt()
{
    ll a;
    cin >> a;
    return a;
}

const int MAXN = 300010;
int N, Q;
ll moves[MAXN];

struct Node
{
    ll sum, lmax, lmin, rmin, mmin;
};

struct ST
{
    Node seg[4 * MAXN];

    Node combine(const Node& n1, const Node& n2)
    {
        Node ans;
        ans.sum = n1.sum + n2.sum;
        ans.lmax = max(n1.sum + n2.lmax, n1.lmax);
        ans.lmin = min(n1.sum + n2.lmin, n1.lmin);
        ans.rmin = min(n1.rmin + n2.sum, n2.rmin);
        ans.mmin = min(min(n1.mmin, n2.mmin),
                       n1.rmin + n2.lmin);
        return ans;
    }

    void update(int a, ll v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = {v, v, v, v, v};
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se)
    {
        if (a > b) return {0, 0, 0, 0, 0};
        if (a <= ss && se <= b) return seg[cid];

        Node ans;
        bool have = 0;
        int mid = (ss + se) / 2;
        if (a <= mid)
        {
            ans = query(a, b, cid * 2, ss, mid);
            have = 1;
        }
        if (b > mid)
        {
            Node n2 = query(a, b, cid * 2 + 1, mid + 1, se);
            if (have) ans = combine(ans, n2);
            else ans = n2;
        }
        return ans;
    }
};

ST seg;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) 
    {
        ll v = readInt();
        seg.update(i, v, 1, 1, N);
    }

    while (Q--)
    {
        int t = readInt();
        if (t == 1)
        {
            int l, r;
            ll H;
            cin >> l >> r >> H;
            ll lb = ceil(H / 10.0);
            
            ll h = H;
            if (l > 1)
            {
                Node a1 = seg.query(1, l - 1, 1, 1, N);
                if (H + a1.mmin <= 0 || h + a1.lmin <= 0)
                {
                    cout << 0 << endl;
                    continue;
                }
                else if (h + a1.lmax >= H)
                {
                    h = H + a1.sum - a1.lmax;
                }
                else h = h + a1.sum;
            }

            if (h <= lb)
            {
                h = lb;
            }
            else
            {
                Node a2 = seg.query(l, r, 1, 1, N);
                if (H + a2.mmin <= lb || h + a2.lmin <= lb)
                {
                    h = lb;
                }
                else if (a2.lmax > H - h)
                {
                    h = H + a2.sum - a2.lmax;
                }
                else h = h + a2.sum;
            }

            if (r < N)
            {
                Node a3 = seg.query(r + 1, N, 1, 1, N);
                if (H + a3.mmin <= 0 || h + a3.lmin <= 0)
                {
                    cout << 0 << endl;
                    continue;
                }
                else if (a3.lmax > H - h)
                {
                    h = H + a3.sum - a3.lmax;
                }
                else h = h + a3.sum;
            }

            cout << h << endl;
        }
        else 
        {
            int a = readInt();
            ll v = readInt();
            seg.update(a, v, 1, 1, N);
        }
    }
    return 0;
}