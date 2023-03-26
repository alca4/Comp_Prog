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
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
#define endl "\n"
ll INF = INT_MAX;
ll LINF = LONG_MAX;
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

const int MAXN = 100010;
int DELTA = 100001;
int N;
int arr[MAXN];
int tarr[MAXN];
vector<int> s;
ll fact[MAXN], factinv[MAXN];

struct ST
{
    ll seg[16 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
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

    void set(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) set(a, v, cid * 2, ss, mid);
        else set(a, v, cid * 2 + 1, mid + 1, se);
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

ST st;

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

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        s.pb(arr[i]);
    }

    sort(s.begin(), s.end());

    int lb = 0, ub = N - 1;
    while (lb <= ub)
    {
        int mid = (lb + ub) / 2;

        for (int i = 1; i <= N; i++) 
        {
            if (arr[i] < s[mid]) tarr[i] = -1;
            else tarr[i] = 1;
            tarr[i] += tarr[i - 1];
        }

        ll lo = 0;
        for (int i = 1; i <= N; i++)
        {
            st.update(tarr[i - 1] + DELTA, 1, 1, DELTA - N, DELTA + N);
            lo += st.query(DELTA + tarr[i] + 1, DELTA + N, 1, DELTA - N, DELTA + N);
        }
        
        for (int i = -N; i <= N; i++) st.set(DELTA + i, 0, 1, DELTA - N, DELTA + N);


        for (int i = 1; i <= N; i++) 
        {
            if (arr[i] > s[mid]) tarr[i] = 1;
            else tarr[i] = -1;
            tarr[i] += tarr[i - 1];
        }

        ll hi = 0;
        for (int i = 1; i <= N; i++)
        {
            st.update(tarr[i - 1] + DELTA, 1, 1, DELTA - N, DELTA + N);
            hi += st.query(DELTA - N, DELTA + tarr[i], 1, DELTA - N, DELTA + N);
        }

        for (int i = -N; i <= N; i++) st.set(DELTA + i, 0, 1, DELTA - N, DELTA + N);

        // cout << "at " << s[mid] << " there are " << lo << " low and " << hi << " high " << endl;

        ll tot = 1ll * N * (N + 1) / 2;
        if ((tot + 1) / 2 <= hi) lb = mid + 1;
        else if (tot / 2 + 1 <= lo) ub = mid - 1;
        else 
        {
            cout << s[mid] << endl;
            break;
        }
    }

    return 0;
} 