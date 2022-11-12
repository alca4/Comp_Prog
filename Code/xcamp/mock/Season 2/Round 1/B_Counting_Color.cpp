/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
int N, C, M;

struct ST
{
    int seg[4 * MAXN];
    int lazy[4 * MAXN];

    void apply(int v, int cid)
    {
        lazy[cid] = seg[cid] = v;
    }

    void push(int cid, int ss, int se)
    {
        if (lazy[cid] != 0 && ss != se)
        {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = 0;
    }

    void update(int a, int b, int v, int cid, int ss, int se)
    {
        if (a <= ss && se <= b)
        {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] | seg[cid * 2 + 1];
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans = ans | query(a, b, cid * 2, ss, mid);
        if (b > mid) ans = ans | query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> C >> M;
    st.update(1, N, 1, 1, 1, N);

    while (M--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a, b, v;
            cin >> a >> b >> v;
            st.update(a, b, (1 << (v - 1)), 1, 1, N);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            int val = st.query(a, b, 1, 1, N);
            int ans = 0;
            while (val > 0)
            {
                ans++;
                val -= (val & -val);
            }
            cout << ans << endl;
        }
    }
    return 0;
}