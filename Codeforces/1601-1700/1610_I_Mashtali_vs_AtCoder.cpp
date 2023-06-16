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
#define EPS 1e-9
// #define cout cerr
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

const int MAXN = 300010;
int N;
int g[MAXN];
int par[MAXN];
vector<int> nbs[MAXN];
int eaten[MAXN];

void DFS(int a, int p) {
    int c = 0;
    for (int nb : nbs[a]) if (nb != p) {
        par[nb] = a;
        DFS(nb, a);
        c++;
        g[a] ^= g[nb] + 1;
    }
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);
    if (g[1]) cout << 1;
    else cout << 2;
    for (int i = 2; i <= N; i++) {
        int t = i;
        int p = par[i];
        while (t != 1 && !eaten[t]) {
            eaten[t] = 1;
            if (p == 1) g[p] ^= g[t] + 1;
            g[t] = 0;
            for (int n : nbs[t]) if (n != par[t] && !eaten[n]) g[1] ^= g[n] + 1;
            g[1] ^= g[t] + 1;

            for (int n : nbs[t]) if (n != par[t] && !eaten[n]) {
                par[n] = 1;
                nbs[1].pb(n);
            }
            
            par[t] = 1;
            nbs[t].clear();
            nbs[1].pb(t);
            t = p;
            p = par[t];
        }

        // for (int i = 1; i <= N; i++) cerr << g[i] << " ";
        // cerr << endl;

        if (g[1]) cout << 1;
        else cout << 2;
    }
    cout << endl;

    return 0;
} 