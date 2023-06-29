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
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        int ans = 0;
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        return ans;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    st.init(1, 1, N);
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) st.update(i, 1, 1, 1, N);

    for (int i = 1; i <= N; i++)
    {
        int k = read();
        int lb = 1;
        int ub = N;

        int ans = 0;
        while (lb <= ub)
        {
            int mid = (lb + ub) / 2;

            int a = st.query(1, mid, 1, 1, N);
            if (a >= k) 
            {
                if (a == k) 
                {
                    if (st.query(mid, mid, 1, 1, N)) 
                    {
                        ans = mid;
                        break;
                    }
                }
                ub = mid - 1;
            }
            else lb = mid + 1;
        }

        cout << arr[ans] << " ";
        st.update(ans, -1, 1, 1, N);
    }
    cout << endl;
    return 0;
}