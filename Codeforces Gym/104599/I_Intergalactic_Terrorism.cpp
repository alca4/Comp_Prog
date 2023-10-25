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
typedef complex<ld> cd;

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
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
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
int N;
int arr[MAXN];
int ans[MAXN];
int best[MAXN];
vector<int> nbs[MAXN];
deque<int> depth[MAXN];

void DFS(int a) {
    depth[a].pb(arr[a]);
    best[a] = arr[a];
    for (int nb : nbs[a]) {
        DFS(nb);
        depth[nb].push_front(0);
        if (depth[a].size() < depth[nb].size()) swap(depth[a], depth[nb]);
        ans[a] = max(ans[a], 1 + best[a] + best[nb]);
        for (int i = 0; i < min(depth[a].size(), depth[nb].size()); i++) {
            depth[a] = max(depth[a], depth[nb]);
            best[a] = max(best[a], depth[a][i] + i);
        }
        best[a] = max(best[a], best[nb] + 1);
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 2; i <= N; i++) {
        int n;
        cin >> n;
        nbs[n].pb(i);
    }

    DFS(1);
    int res = 0;
    for (int i = 1; i <= N; i++) res = max(res, ans[i]);
    cout << res << endl;

    return 0;
} 