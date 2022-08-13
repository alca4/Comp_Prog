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

const int MAXN = 1010;
int N, Q;
int arr[MAXN];

struct ST
{
    ll seg[4 * MAXN];

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

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    }
} bit[MAXN];

void update(int a, int b)
{
    while (a <= N)
    {
        bit[a].update(b, 1, 1, 1, N);
        a += (a & -a);
    }
}

int query(int a, int b, int d)
{
    int sum = 0;
    while (a > 0)
    {
        sum += bit[a].query(b, d, 1, 1, N);
        a -= (a & -a);
    }
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
    {
        char c;
        cin >> c;
        if (c == '*') update(i, j);
    }

    while (Q--)
    {
        int a = read(), b = read(), c = read(), d = read();
        cout << query(c, b, d) - query(a - 1, b, d) << endl;
    }
    return 0;
}