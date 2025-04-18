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
ll MOD = 0;

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

const int MAXN = 100010;
int N, Q;
ll arr[MAXN];
vector<int> nbs[MAXN];
set<pii> nbs2[MAXN];
int sz[MAXN];
int par[MAXN];

void DFS(int a, int p) {
    par[a] = p;
    sz[a] = 1;
    for (int nb : nbs[a]) if (nb != p) {
        DFS(nb, a);
        sz[a] += sz[nb];
        arr[a] += arr[nb];
        nbs2[a].insert({sz[nb] * -1, nb});
    }
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);

    while (Q--) {
        int t, v;
        cin >> t >> v;
        if (t == 1) cout << arr[v] << endl;
        else {
            if (nbs2[v].empty()) continue;

            int s = nbs2[v].begin()->SS;
            int p = par[v];

            nbs2[v].erase({sz[s] * -1, s});
            nbs2[p].erase({sz[v] * -1, v});

            arr[v] -= arr[s];
            sz[v] -= sz[s];
            arr[s] += arr[v];
            sz[s] += sz[v];

            nbs2[s].insert({sz[v] * -1, v});
            nbs2[p].insert({sz[s] * -1, s});

            par[s] = p;
            par[v] = s;
        }
    }

    return 0;
} 