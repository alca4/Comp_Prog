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
ll INF = 1000000000;
ll MOD = 1000000007;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll div(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

const int MAXN = 100010;
int N, M;

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

    void apply(ll v, int cid)
    {
        lazy[cid] = lazy[cid] | v;
        seg[cid] = seg[cid] | v;
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
        seg[cid] = seg[cid * 2] & seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = ((1 << 30) - 1) * 2 + 1;
        if (a <= mid) ans = ans & query(a, b, cid * 2, ss, mid);
        if (b > mid) ans = ans & query(a, b, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] & seg[cid * 2 + 1];
        return ans;
    }
};

struct Query
{
    int l, r, q;
} queries[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
    {
        int l, r, q;
        cin >> l >> r >> q;
        queries[i] = {l, r, q};
    }

    ST st;
    for (int i = 1; i <= M; i++) st.update(queries[i].l, queries[i].r, queries[i].q, 1, 1, N);

    bool ok = 1;
    for (int i = 1; i <= M; i++) 
        if (st.query(queries[i].l, queries[i].r, 1, 1, N) != queries[i].q) ok = 0;
    
    if (ok) 
    {
        cout << "YES" << endl;
        for (int i = 1; i <= N; i++) cout << st.query(i, i, 1, 1, N) << " ";
        cout << endl;
    }
    else cout << "NO" << endl;
    return 0;
} 