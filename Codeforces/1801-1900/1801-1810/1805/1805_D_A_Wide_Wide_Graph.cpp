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
ll MOD = LINF;
// ll MOD = 1000000007;
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
int N;
vector<int> nbs[MAXN];
pii d[3][MAXN];
int dist[MAXN];
int ans[MAXN];
// ll fact[MAXN], factinv[MAXN];

// ll choose(int a, int b)
// {
//     return mult(fact[a], mult(factinv[b], factinv[a - b]));
// }

// void get_fact(int x)
// {
//     fact[0] = 1;
//     for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
//     factinv[x] = divide(1, fact[x]);
//     for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
// }

void DFS(int a, int p, int t)
{
    for (int nb : nbs[a]) if (nb != p)
    {
        d[t][nb] = pii(d[t][a].FF + 1, nb);
        DFS(nb, a, t);
    }
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
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0, 0);
    sort(d[0] + 1, d[0] + 1 + N, greater<pii>());
    DFS(d[0][1].SS, 0, 1);
    sort(d[1] + 1, d[1] + 1 + N, greater<pii>());
    int dia = d[1][1].FF;
    DFS(d[1][1].SS, 0, 2);

    for (int i = 1; i <= N; i++) maxeq(dist[d[1][i].SS], d[1][i].FF);
    for (int i = 1; i <= N; i++) maxeq(dist[d[2][i].SS], d[2][i].FF);
    for (int i = 1; i <= N; i++) ans[dist[i]]++;
    ans[dia]--;
    ans[N + 1] = N;
    for (int i = N; i >= 1; i--) ans[i] = ans[i + 1] - ans[i];
    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;

    return 0;
} 