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
#define INF 1000000000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
int N;
int arr[MAXN];
struct Iv
{
    ll v;
    int n1, n2;
} itv[2 * MAXN];
int done[2 * MAXN];

bool CompV(const Iv& i1, const Iv& i2)
{
    return i1.v < i2.v;
}

struct ST
{
    struct Node
    {
        int r;
        int nl;
        int nr;
    } seg[8 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            // cout << "updated " << a << " with " << v << endl;
            seg[cid] = {v, 0, 0};
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);

        seg[cid].nl = max(seg[cid * 2].nl, seg[cid * 2 + 1].r);
        seg[cid].nr = max(seg[cid * 2].r, seg[cid * 2 + 1].nr);
        seg[cid].r = max(seg[cid * 2].nr, seg[cid * 2 + 1].nl);

        ll a1, a2 = INF;
        if (!done[mid + N] || (done[mid] + done[mid + 1] == 1))
            a1 = max(seg[cid].r, arr[mid] + arr[mid + 1]);

        a2 = max(seg[cid * 2].r, seg[cid * 2 + 1].r);
        
        // seg[cid].r = min(min(a1, a2), a3);

        // if (seg[cid] == a2 && seg[cid] != a1 && seg[cid] != a3)            
    }

    void clear(int cid, int ss, int se)
    {
        seg[cid] = {0, 0, 0};
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }
};

ST seg;

void solve()
{
    cout << "=====" << endl;
    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) seg.update(i, arr[i], 1, 1, N);

    for (int i = 1; i <= N - 1; i++) 
        itv[i] = {arr[i] + arr[i + 1], i, i + 1};
    for (int i = N; i < 2 * N; i++)
        itv[i] = {arr[i - N + 1], i - N + 1, -1};

    sort(itv + 1, itv + 2 * N, CompV);

    for (int i = 1; i < 2 * N; i++)
        cout << itv[i].v << " " << itv[i].n1 << " " << itv[i].n2 << endl;
    
    ll ans = INF;
    for (int i = 1; i <= N; i++)
    {
        cout << i << endl;
        ans = min(ans, seg.seg[1].r - itv[i].v);
        cout << "ans could be: " << seg.seg[1].r - itv[i].v << endl;

        if (itv[i].n2 == -1)
        {
            if (!done[itv[i].n1 + N] || !done[itv[i].n1 - 1 + N])
                seg.update(itv[i].n1, 0, 1, 1, N);
            else break;
            
            done[itv[i].n1] = 1;
        }
        else
        {
            if (!done[itv[i].n1] && !done[itv[i].n2])
                done[itv[i].n1 + 1] = 1;
            else break;
        }
    }

    cout << ans << endl;

    seg.clear(1, 1, N);
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i < 2 * N; i++) 
    {
        itv[i] = {0, 0, 0};
        done[i] = 0;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}