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
int N, A, B;
vector<pii> nbs[MAXN];
int df[MAXN][2];
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

void DFS(int a, int p, int t)
{
    for (pii nb : nbs[a]) if (nb.FF != p && nb.FF != B)
    {
        df[nb.FF][t] = df[a][t] ^ nb.SS;
        DFS(nb.FF, a, t);
    }
}

void solve()
{
    cin >> N >> A >> B;
    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
        nbs[b].pb({a, c});
    }

    for (int i = 1; i <= N; i++) df[i][0] = INF;
    for (int i = 1; i <= N; i++) df[i][1] = -INF;

    df[A][0] = 0;
    df[B][1] = 0;

    DFS(A, 0, 0);
    DFS(B, 0, 1);

    map<int, int> a, b;
    for (int i = 1; i <= N; i++) a[df[i][0]]++;
    for (int i = 1; i <= N; i++) if (i != B) b[df[i][1]]++;

    int ans = 0;
    for (auto n : a)
        if (b.count(n.FF)) ans = 1;

    if (ans) cout << "YES" << endl;
    else cout << "NO" << endl;

    a.clear();
    b.clear();
    for (int i = 1; i <= N; i++) df[i][0] = df[i][1] = 0;
    for (int i = 1; i <= N; i++) nbs[i].clear();
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