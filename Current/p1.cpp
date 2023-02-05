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

Praise to the Cow God
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 2000010;
int N, Q;

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

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
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = INF;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }
};

ST st;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        int n;
        cin >> n;
        st.update(i, i, n, 1, 1, N);
    }

    int ans = -1;
    for (int i = 1; i <= Q; i++)
    {
        int x, l, r;
        cin >> x >> l >> r;
        if (st.query(l, r, 1, 1, N) < x)
        {
            ans = i;
            break;
        }
        else st.update(l, r, -x, 1, 1, N);
    }

    if (ans == -1) cout << 0 << endl;
    else 
    {
        cout << -1 << endl;
        cout << ans << endl;
    }
    return 0;
} 