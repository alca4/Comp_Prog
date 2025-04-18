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

const int MAXN = 200010;
int N, K;
vector<int> nbs[MAXN];
int depth[MAXN];
vector<int> d[MAXN];
int vis[MAXN];

void DFS(int a, int p) {
    d[depth[a]].pb(a);
    for (int nb : nbs[a]) if (nb != p) {
        depth[nb] = depth[a] + 1;
        DFS(nb, a);
    }
}

void DFS2(int a, int p, int l) {
    vis[a] = 1;
    for (int nb : nbs[a]) if (nb != p && depth[nb] >= l && !vis[nb]) DFS2(nb, a, l);
}

int test(int a) {
    int ops = 0;
    for (int i = N; i > a; i--) 
        for (int j : d[i]) if (!vis[j]) {
            DFS2(j, 0, i - a + 1);
            ops++;
        } 
    for (int i = 1; i <= N; i++) vis[i] = 0;
    return ops;
}

void solve() {
    cin >> N >> K;
    for (int i = 2; i <= N; i++) {
        int n;
        cin >> n;
        nbs[n].pb(i);
        nbs[i].pb(n);
    }

    DFS(1, 0);

    int lb = 1;
    int ub = N;
    int ans = N;
    while (lb <= ub) {
        int mid = (lb + ub) / 2;

        if (test(mid) <= K) {
            ans = mid;
            ub = mid - 1;
        }
        else lb = mid + 1;
    }

    cout << ans << endl;
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        depth[i] = 0;
        d[i].clear();
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

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 