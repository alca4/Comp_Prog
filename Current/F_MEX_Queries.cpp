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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 100010;
int Q;

map<int, int> compress;
map<int, int> unravel;

struct ST
{
    ll seg[8 * MAXN], l1[8 * MAXN], l2[8 * MAXN];

    void apply1(int v, int cid, int ss, int se)
    {
        l1[cid] = v;
        if (v == 1) seg[cid] = se - ss + 1;
        if (v == -1) seg[cid] = 0;
    }

    void apply2(int v, int cid, int ss, int se)
    {
        if (v)
        {
            l2[cid] = 1;
            seg[cid] = se - ss + 1 - seg[cid];
        }
    }

    void push(int cid, int ss, int se)
    {
        if (ss != se)
        {
            int mid = (ss + se) / 2;
            apply1(l1[cid], cid * 2, ss, mid);
            apply1(l1[cid], cid * 2 + 1, mid + 1, se);

            apply2(l2[cid], cid * 2, ss, mid);
            apply2(l2[cid], cid * 2 + 1, mid + 1, se);
        }
        l1[cid] = 0;
    }

    void update1(int a, int b, int v, int cid, int ss, int se)
    {
        if (a <= ss && se <= b)
        {
            apply1(v, cid, ss, se);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) update1(a, b, v, cid * 2, ss, mid);
        if (b > mid) update1(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = 0;
        if (a <= mid) ans = query(a, b, cid * 2, ss, mid);
        if (b > mid) ans = query(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }
};

struct Query
{
    int t, l, r;
} queries[MAXN];

ST st;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> Q;
    compress[1] = 1;
    for (int i = 1; i <= Q; i++)
    {
        int t, l, r;
        cin >> t >> l >> r;
        queries[i] = {t, l, r};
        compress[l] = 1;
        compress[r] = 1;
    }

    int cnt = 0;
    for (auto n : compress) compress[n.FF] = ++cnt;
    for (auto n : compress) unravel[n.SS] = n.FF;
    int N = compress.size();

    unravel[0] = 0;

    for (int i = 1; i <= Q; i++)
    {
        if (queries[i].t == 1) st.update(compress[queries[i].l], compress[queries[i].r], 1, 1, 1, N);
        if (queries[i].t == 2) st.update(compress[queries[i].l], compress[queries[i].r], -1, 1, 1, N);
        if (queries[i].t == 3) st.update(compress[queries[i].l], compress[queries[i].r], -1, 1, 1, N);
        cout << st.query(1, N, 1, 1, N) << endl;
    }
    return 0;
} 