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
#define INF (int) 1000000000
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

const int MAXN = 500010;
int N, Q;
int arr[MAXN];

struct ST
{
    struct Node
    {
        int v, lc, rc;
    };

    vector<Node> seg;

    int create()
    {
        int a = seg.size();
        Node n = {0, -1, -1};
        seg.pb(n);
        return a;
    }

    int update(int a, ll v, int cid, int ss, int se)
    {
        if (cid == -1) cid = create();
        if (ss == se)
        {
            seg[cid].v += v;
            return cid;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) seg[cid].lc = update(a, v, seg[cid].lc, ss, mid);
        else seg[cid].rc = update(a, v, seg[cid].rc, mid + 1, se);

        int ans = 0;
        if (seg[cid].lc != -1) ans += seg[seg[cid].lc].v;
        if (seg[cid].rc != -1) ans += seg[seg[cid].rc].v;
        seg[cid].v = ans;
        return cid;
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid].v;

        int mid = (ss + se) / 2;
        int ans = 0;
        if (a <= mid && seg[cid].lc != -1) ans += query(a, b, seg[cid].lc, ss, mid);
        if (b > mid && seg[cid].rc != -1) ans += query(a, b, seg[cid].rc, mid + 1, se);
        return ans;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    st.create();

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        st.update(arr[i], 1, 0, 1, INF);
    }

    while (Q--)
    {
        char c;
        cin >> c;

        if (c == '?')
        {
            int a, b;
            cin >> a >> b;
            cout << st.query(a, b, 0, 1, INF) << endl;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            st.update(arr[a], -1, 0, 1, INF);
            st.update(b, 1, 0, 1, INF);
            arr[a] = b;
        }
    }
    return 0;
}