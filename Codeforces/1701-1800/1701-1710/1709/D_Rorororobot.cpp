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

const int MAXN = 100010;
int N, M, Q;
int block[200010];

int seg[800010];

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
    seg[cid] = max(seg[cid * 2], seg[cid * 2 + 1]);
}

int query(int a, int b, int cid, int ss, int se)
{
    if (a <= ss && se <= b) return seg[cid];

    int ans = 0;
    int mid = (ss + se) / 2;
    if (a <= mid) ans = max(ans, query(a, b, cid * 2, ss, mid));
    if (b > mid) ans = max(ans, query(a, b, cid * 2 + 1, mid + 1, se));
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) cin >> block[i];
    for (int i = 1; i <= M; i++) update(i, block[i], 1, 1, M);

    cin >> Q;
    while (Q--)
    {
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;

        bool ans = 1;
        if (abs(x2 - x1) % k != 0) ans = 0;
        if (abs(y2 - y1) % k != 0) ans = 0;
        
        int a = (N - x1) % k;
        int tar = N - a;

        if (y2 < y1) swap(y1, y2);
        ans &= (query(y1, y2, 1, 1, M) < tar);

        if (ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}