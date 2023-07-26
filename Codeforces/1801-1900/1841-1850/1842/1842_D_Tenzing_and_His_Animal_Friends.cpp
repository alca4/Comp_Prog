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

const int MAXN = 110;
int N, M;
ll adjmat[MAXN][MAXN];
vector<pll> nbs[MAXN];
ll w[MAXN];

struct Game {
    string str;
    ll t;
};
vector<Game> games;

int vis[MAXN];
ll DFS(int a) {
    vis[a] = 1;
    ll x = w[a];
    for (pii nb : nbs[a]) if (!vis[nb.FF] && w[nb.FF] > 0) {
        x = min(x, DFS(nb.FF));
    }
    return x;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) adjmat[i][j] = LINF;
    for (int i = 1; i <= N; i++) adjmat[i][i] = 0;

    for (int i = 1; i <= M; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        nbs[a].pb({b, c});
        nbs[b].pb({a, c});
        adjmat[a][b] = adjmat[b][a] = c;
    }

    for (int k = 1; k <= N; k++) 
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
    
    if (adjmat[1][N] == LINF) {
        cout << "inf" << endl;
        return 0;
    }

    w[1] = adjmat[1][N];
    for (int i = 1; i <= N; i++) w[i] = min(adjmat[N][i], w[1]);

    while (w[1]) {
        Game g;
        g.str.resize(N);
        g.t = LINF;
        for (int i = 1; i <= N; i++) if (!vis[i] && w[i]) {
            g.t = min(g.t, DFS(i));
        }
        for (int j = 1; j <= N; j++) {
            if (vis[j]) {
                vis[j] = 0;
                g.str[j - 1] = '1';
                w[j] -= g.t;
            }
            else g.str[j - 1] = '0';
        }
        games.pb(g);
    }

    cout << adjmat[1][N] << " " << games.size() << endl;
    for (int i = 0; i < games.size(); i++) {
        cout << games[i].str << " " << games[i].t << endl;
    }

    return 0;
} 