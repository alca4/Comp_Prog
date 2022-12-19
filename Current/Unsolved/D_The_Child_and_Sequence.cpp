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
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

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

const int MAXN = 100010;
int N, Q;

struct ST
{
    ll seg[4 * MAXN];
    int lazy[4 * MAXN];

    ST(int N) {init(1, 1, N);}

    void init(int cid, int ss, int se)
    {
        seg[cid] = 0;
        lazy[cid] = INF;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        init(cid * 2, ss, mid);
        init(cid * 2 + 1, mid + 1, se);
    }

    void apply(int v, int cid)
    {
        lazy[cid] = min(lazy[cid], v);
        seg[cid] %= v;
    }

    void push(int cid, int ss, int se)
    {
        if (ss != se && lazy[cid] != INF)
        {
            apply(lazy[cid], cid * 2);
            apply(lazy[cid], cid * 2 + 1);
        }
        lazy[cid] = INF;
    }

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

    void modby(int a, int b, int v, int cid, int ss, int se)
    {
        if (a > b) return;
        if (a <= ss && se <= b)
        {
            apply(v, cid);
            return;
        }

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        if (a <= mid) modby(a, b, v, cid * 2, ss, mid);
        if (b > mid) modby(a, b, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        push(cid, ss, se);
        int mid = (ss + se) / 2;
        ll ans = INF;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
        return ans;
    }
};

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    ST st(N);
    for (int i = 1; i <= N; i++) 
    {
        int a;
        cin >> a;
        st.update(i, a, 1, 1, N);
    }

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a, b;
            cin >> a >> b;
            cout << st.query(a, b, 1, 1, N) << endl;
        }
        if (t == 2)
        {
            int a, b, x;
            cin >> a >> b >> x;
            // st.modby(a, b, x, 1, 1, N);
        }
        if (t == 3)
        {
            int a, x;
            cin >> a >> x;
            // st.update(a, x, 1, 1, N);
        }
    }

    return 0;
} 