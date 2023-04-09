/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
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
#define endl "\n"
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

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

const int MAXN = 300010;
int N, M;
int arr[MAXN];
int h[MAXN], c[MAXN];
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

struct ST
{
    ll seg[4 * MAXN], lazy[4 * MAXN];

    void clear(int cid, int ss, int se)
    {
        seg[cid] = lazy[cid] = 0;
        if (ss == se) return;

        int mid = (ss + se) / 2;
        clear(cid * 2, ss, mid);
        clear(cid * 2 + 1, mid + 1, se);
    }

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
        ll ans = 9ll * LINF;
        if (a <= mid) ans = min(ans, query(a, b, cid * 2, ss, mid));
        if (b > mid) ans = min(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
        return ans;
    }
};

ST dp;

void solve()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) cin >> c[i];
    for (int i = 1; i <= M; i++) cin >> h[i];

    M++;
    arr[0] = M;

    dp.update(1, M - 1, LINF, 1, 1, M);

    for (int i = 1; i <= N; i++)
    {
        ll t1 = dp.query(1, M, 1, 1, M) + c[arr[i]];
        ll t2 = dp.query(arr[i], arr[i], 1, 1, M) + h[arr[i]];

        if (arr[i] != arr[i - 1]) dp.update(1, M, c[arr[i]], 1, 1, M);
        else dp.update(1, M, h[arr[i]], 1, 1, M);

        ll t3 = dp.query(arr[i - 1], arr[i - 1], 1, 1, M);
        dp.update(arr[i - 1], arr[i - 1], min({t1, t2, t3}) - t3, 1, 1, M);
    }

    cout << dp.query(1, M, 1, 1, M) << endl;
    
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i <= M; i++) c[i] = h[i] = 0;

    dp.clear(1, 1, M);
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 