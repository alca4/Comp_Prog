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
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;

struct ST
{
    ll seg[4 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    } 
};

int N, Q;
struct Query
{
    int n1, n2, id;

    bool operator<(const Query& q)
    {
        return pii(n2, n1) < pii(q.n2, q.n1);
    }
} queries[MAXN];
ST st;
int ans[MAXN];
int arr[MAXN];
int lv[MAXN];
map<int, int> last;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q; 
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= Q; i++) cin >> queries[i].n1 >> queries[i].n2, queries[i].id = i;

    for (int i = 1; i <= N; i++) 
    {
        if (last.find(arr[i]) == last.end()) lv[i] = -1;
        else lv[i] = last[arr[i]];
        last[arr[i]] = i;
        // cout << lv[i] << " ";
    }
    // cout << endl;

    sort(queries + 1, queries + 1 + Q);
    int r = 0;
    for (int i = 1; i <= Q; i++)
    {
        while (r < queries[i].n2)
        {
            r++;
            st.update(r, 1, 1, 1, N);
            if (lv[r] > 0) st.update(lv[r], 0, 1, 1, N);
        }
        ans[queries[i].id] = st.query(queries[i].n1, queries[i].n2, 1, 1, N);
    }
    
    for (int i = 1; i <= Q; i++) cout << ans[i] << endl;
    return 0;
}