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

const int MAXN = 200010;
int N, H;
int h[MAXN], hfreq[MAXN];
vector<int> nbs[MAXN];
ll pow2[MAXN], fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[N]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

void get_pow2()
{
    pow2[0] = 1;
    for (int i = 1; i <= N; i++) pow2[i] = mult(pow2[i - 1], 2);
}

void DFS(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) 
    {
        DFS(nbs[a][i], a);
        h[a] = max(h[a], h[nbs[a][i]] + 1);
    }
    hfreq[h[a]]++;
    H = max(H, h[a]);
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
    while (T--)
    {
        cin >> N;
        get_pow2();
        for (int i = 1; i < N; i++) 
        {
            int a, b;
            cin >> a >> b;
            nbs[a].pb(b);
            nbs[b].pb(a);
        }

        DFS(1, 0);

        ll ans = 0;
        int x = N;
        for (int i = 0; i <= H; i++) 
        {
            ans = add(ans, mult(x, pow2[N - 1]));
            x -= hfreq[i];
        }

        cout << ans << endl;
        for (int i = 0; i <= N; i++) h[i] = hfreq[i] = 0;
        for (int i = 1; i <= N; i++) nbs[i].clear();
        H = 0;
    }

    return 0;
} 