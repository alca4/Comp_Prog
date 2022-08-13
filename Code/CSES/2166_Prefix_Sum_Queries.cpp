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
#define INF 1000000000000000000
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
ll arr[MAXN];

struct ST
{
    ll seg[4 * MAXN];
    ll lazy[4 * MAXN];

    void init(int cid, int ss, int se)
    {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;
        
        int mid = (ss + se) / 2;
        init(cid * 2, ss, mid);
        init(cid * 2 + 1, mid + 1, se);
    }

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
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll maxv = -INF;
        if (a <= mid) maxv = max(maxv, query(a, b, cid * 2, ss, mid));
        if (b > mid) maxv = max(maxv, query(a, b, cid * 2 + 1, mid + 1, se));
        return maxv;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    st.init(1, 1, N);
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        st.update(i, N, arr[i], 1, 1, N);
    }
    // for (int i = 1; i <= N; i++) cout << st.query(i, i, 1, 1, N) << " ";
    // cout << endl;

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a, b;
            cin >> a >> b;
            st.update(a, N, b - arr[a], 1, 1, N);
            // for (int i = 1; i <= N; i++) cout << st.query(i, i, 1, 1, N) << " ";
            // cout << endl;
            arr[a] = b;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            ll ans = st.query(a, b, 1, 1, N);
            ll pref = 0;
            if (a > 1) pref = st.query(a - 1, a - 1, 1, 1, N);
            cout << max(ans, pref) - pref << endl;
        }
        // for (int i = 1; i <= 2 * N; i++) cout << st.seg[i] << " ";
        // cout << endl;
    }
    return 0;
}