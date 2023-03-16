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
ll INF = 2000000000;
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

const int MAXN = 100010, D = 100000;
int R, C, N;
ll val[MAXN * 2];
int vis[MAXN * 2];
vector<pll> nbs[MAXN * 2];
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

vector<int> friends;
int DFS(int a)
{
    // cout << "at " << a << endl;
    vis[a] = 1;
    friends.pb(a);
    int x = 1;
    for (pll nb : nbs[a]) 
    {
        if (val[nb.FF] != -LINF && val[nb.FF] + val[a] != nb.SS) return 0;
        val[nb.FF] = nb.SS - val[a];
        if (!vis[nb.FF]) x = (x & DFS(nb.FF));
    }
    return x;
}

int check(int i)
{
    int ans = 1;
    val[i] = 0;
    ans &= DFS(i);

    ll min_r = LINF;
    ll min_c = LINF;
    for (int n : friends) if (val[n] != -LINF) 
    {
        if (n <= D) min_r = min(min_r, val[n]);
        else min_c = min(min_c, val[n]);
    }
    min_r *= -1;
    ans &= (min_r <= min_c);
    friends.clear();
    return ans;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> C >> N;
    for (int i = 1; i <= N; i++)
    {
        ll r, c, x;
        cin >> r >> c >> x;
        nbs[r].pb({c + D, x});
        nbs[c + D].pb({r, x});
    }

    for (int i = 1; i <= R; i++) val[i] = -LINF;
    for (int i = 1; i <= C; i++) val[i + D] = -LINF;

    int ans = 1;
    for (int i = 1; i <= R; i++) if (!vis[i]) ans &= check(i);
    for (int i = 1; i <= C; i++) if (!vis[i + D]) ans &= check(i + D);
    
    if (ans) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
} 