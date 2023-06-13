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

const int MAXN = 200010;
int N, M;
ll K;
pii arr[MAXN];
vector<int> nbs[MAXN];
int w[MAXN];
int vis[MAXN];
ll depth[MAXN];
int in_stack[MAXN];

ll DFS(int a, int mid) {
    vis[a] = 1;
    in_stack[a] = 1;
    for (int nb : nbs[a]) if (w[nb] <= mid) {
        if (in_stack[nb]) {
            in_stack[a] = 0;
            depth[a] = LINF;
            return depth[a];
        }
        if (vis[nb]) depth[a] = max(depth[a], depth[nb]);
        else depth[a] = max(depth[a], DFS(nb, mid));
    }
    in_stack[a] = 0;
    depth[a] = depth[a] + 1;
    return depth[a];
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i].FF;
        arr[i].SS = i;
    }

    sort(arr + 1, arr + 1 + N);

    for (int i = 1; i <= N; i++) w[arr[i].SS] = i;

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
    }

    ll lb = 1, ub = N;
    ll ans = LINF;
    while (lb <= ub) {
        ll mid = (lb + ub) / 2;
        // cout << mid << endl;

        ll best = 0;
        for (int i = 1; i <= mid; i++) 
            if (!vis[arr[i].SS]) best = max(best, DFS(arr[i].SS, mid));
        for (int i = 1; i <= mid; i++) vis[arr[i].SS] = depth[arr[i].SS] = 0;

        if (best >= K) {
            ans = arr[mid].FF;
            ub = mid - 1;
        }
        else lb = mid + 1;
    }
    if (ans == LINF) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
} 