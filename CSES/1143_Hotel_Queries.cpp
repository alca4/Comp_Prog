/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz

BTW this problem was in fact solved in a hotel room
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

struct ST
{
    ll seg[4 * MAXN];

    void init(int cid, int ss, int se)
    {
        seg[cid] = 0;
        if (ss == se) return;
        
        int mid = (ss + se) / 2;
        init(cid * 2, ss, mid);
        init(cid * 2 + 1, mid + 1, se);
    }

    void update(int a, ll v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] += v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
        // cout << ss << " " << se << endl;
        // cout << seg[cid] << " " << seg[cid * 2] << " " << seg[cid * 2 + 1] << endl;
    }

    int query(int a, int cid, int ss, int se)
    {
        if (ss == se) 
        {
            if (seg[cid] >= a) return ss;
            return INF;
        }

        int mid = (ss + se) / 2;
        if (seg[cid * 2] < a) return query(a, cid * 2 + 1, mid + 1, se);
        else return query(a, cid * 2, ss, mid);
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
    for (int i = 1; i <= N; i++) st.update(i, read(), 1, 1, N);

    while (Q--)
    {
        int a = read();
        // cout << "processing " << a << endl;
        int v = st.query(a, 1, 1, N);
        if (v == INF)
        {
            cout << "0 ";
            continue;
        }
        cout << v << " ";
        st.update(v, -a, 1, 1, N);
    }
    cout << endl;
    return 0;
}