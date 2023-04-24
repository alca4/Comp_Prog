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
ll MOD = 998244353;

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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
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

const int MAXN = 525000;
int N, M;
vector<ll> a, b;

void dft(vector<ll>& a, int tot, bool inv)
{
    ll g = 3;
    if (inv) g = power(g, MOD - 2);
    int sz = (1 << tot);
    for (int i = 1, j = 0; i < sz; i++) {
        int bit = sz >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int i = 0; i < tot; i++) 
    {
        vector<ll> w((1 << i));
        w[0] = 1;
        ll t = power(g, (MOD - 1) / (1 << (i + 1)));
        for (int j = 1; j < (1 << i); j++) w[j] = (w[j - 1] * t) % MOD;
        for (int j = 0; j < sz; j += (1 << (i + 1)))
        {
            for (int k = 0; k < (1 << i); k++)
            {
                ll f = add(a[j + k], mult(w[k], a[j + k + (1 << i)]));
                ll s = sub(a[j + k], mult(w[k], a[j + k + (1 << i)]));
                a[j + k] = f;
                a[j + k + (1 << i)] = s;
            }
        }
    }

    if (inv)
    {
        ll szinv = power(sz, MOD - 2);
        for (int i = 0; i < sz; i++) a[i] = mult(a[i], szinv);
    }
}

vector<ll> fft(vector<ll>& a, vector<ll>& b)
{
    ll g = 3;
    int tot = 32 - __builtin_clz(a.size() + b.size() - 2);
    if (a.size() == 1 && b.size() == 1) tot = 0;
    int sz = (1 << tot);

    while (a.size() < sz) a.pb(0);
    while (b.size() < sz) b.pb(0);

    dft(a, tot, 0);
    dft(b, tot, 0);

    vector<ll> c(sz);
    for (int i = 0; i < sz; i++) c[i] = mult(a[i], b[i]);

    dft(c, tot, 1);
    return c;
}


int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    a.resize(N);
    b.resize(M);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < M; i++) cin >> b[i];
    vector<ll> c = fft(a, b);
    for (int i = 0; i < c.size(); i++) cout << c[i] << " ";
    cout << endl;

    return 0;
} 