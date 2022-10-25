/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int MAXN = 500010;

pll combine(pll p1, pll p2)
{
    if (p1.FF == p2.FF) return pll(p1.FF, p1.SS + p2.SS);
    return min(p1, p2);
}

struct ST
{
    pll seg[4 * MAXN];
    ll lazy[4 * MAXN];

    void apply(ll v, int cid)
    {
        lazy[cid] += v;
        seg[cid].FF += v;
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

    void set(int a, ll v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = pll(v, 1);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    void update(int a, int b, ll v, int cid, int ss, int se)
    {
        if (a > b) return;
        if (a <= ss && se <= b)
        {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update(a, b, v, cid * 2, ss, mid);
        if (b > mid) update(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    pll query(int a, int b, int cid, int ss, int se)
    {
        if (a > b) return {INF, INF};
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        pll a1 = {INF, INF}, a2 = {INF, INF};
        if (a <= mid) a1 = query(a, b, cid * 2, ss, mid);
        if (b > mid) a2 = query(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
        return combine(a1, a2);
    }

    int findBest(int cid, int ss, int se)
    {
        push(cid, ss, se);
        if (seg[cid].FF >= 0) return 1000000000;
        if (ss == se) return ss;

        assert(seg[cid].FF < 0);
        assert(combine(seg[cid * 2], seg[cid * 2 + 1]).FF < 0);

        int mid = (ss + se) / 2;
        if (seg[cid * 2].FF < 0) return findBest(cid * 2, ss, mid);
        return findBest(cid * 2 + 1, mid + 1, se);
    }
};

ST odd, even;
int N;
ll arr[MAXN];

pll query(int a, int b)
{
    if (a % 2 == 0 && b % 2 == 0) 
        return combine(odd.query(a / 2 + 1, b / 2, 1, 1, (N + 1) / 2), 
                       even.query(a / 2, b / 2, 1, 1, N / 2));
    if (a % 2 == 1 && b % 2 == 0) 
        return combine(odd.query((a + 1) / 2, b / 2, 1, 1, (N + 1) / 2), 
                       even.query((a + 1) / 2, b / 2, 1, 1, N / 2));
    if (a % 2 == 0 && b % 2 == 1) 
        return combine(odd.query(a / 2 + 1, (b + 1) / 2, 1, 1, (N + 1) / 2), 
                       even.query(a / 2, b / 2, 1, 1, N / 2));
    if (a % 2 == 1 && b % 2 == 1) 
        return combine(odd.query((a + 1) / 2, (b + 1) / 2, 1, 1, (N + 1) / 2), 
                       even.query((a + 1) / 2, b / 2, 1, 1, N / 2));
    return {0, 0}; // if this fires i will be mad
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N;
    ll sum = 0;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        sum = arr[i] - sum;
        if (i % 2) odd.set((i + 1) / 2, sum, 1, 1, (N + 1) / 2);
        else even.set(i / 2, sum, 1, 1, N / 2);
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++)
    {
        int lb = i;
        int ub = N;

        int oi = odd.findBest(1, 1, (N + 1) / 2) * 2 - 1;
        int ei = even.findBest(1, 1, N / 2) * 2;

        // for (int i = 1; i <= N; i++) cout << query(i, i).FF << " ";
        // cout << endl;
        
        // cout << oi << " " << ei << endl;

        int re = min(min(oi, ei) - 1, N);

        // cout << i << " to " << re << endl;

        pll it = query(i, re);

        if (it.FF == 0) ans += it.SS;

        if (i % 2) 
        {
            odd.update((i + 1) / 2, (N + 1) / 2, -1 * arr[i], 1, 1, (N + 1) / 2);
            even.update((i + 1) / 2, N / 2, arr[i], 1, 1, N / 2);
        }
        else 
        {
            odd.update(i / 2 + 1, (N + 1) / 2, arr[i], 1, 1, (N + 1) / 2);
            even.update(i / 2, N / 2, -1 * arr[i], 1, 1, N / 2);
        }
    }

    cout << ans << endl;

    for (int i = 1; i <= N; i++) 
    {
        arr[i] = 0;
        if (i % 2) odd.set((i + 1) / 2, 0, 1, 1, (N + 1) / 2);
        else even.set(i / 2, 0, 1, 1, N / 2);
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