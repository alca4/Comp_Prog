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

const int MAXN = 460;
int N, M, K1, K2, S, T;

vector<vector<ll>> dist[MAXN];
vector<vector<int>> vis[MAXN];
vector<pii> nbs[MAXN][3];

struct Loc {
    ll w;
    int n, k1, k2;
};

bool operator<(const Loc& l1, const Loc& l2) {
    return l1.w > l2.w;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> K1 >> K2;
    for (int i = 1; i <= M; i++) {
        int a, b, c, t;
        cin >> a >> b >> c >> t;
        nbs[a][t].pb(pii(b, c));
        nbs[b][t].pb(pii(a, c));
    }

    for (int i = 1; i <= N; i++) {
        dist[i].resize(K1 + 1);
        vis[i].resize(K1 + 1);
        for (int j = 0; j <= K1; j++) {
            dist[i][j].resize(K2 + 1);
            vis[i][j].resize(K2 + 1);
            for (int k = 0; k <= K2; k++) {
                // cout << i << " " << j << " " << k << endl;
                dist[i][j][k] = LINF;
            }
        }
    }

    cin >> S >> T;
    dist[S][0][0] = 0;

    priority_queue<Loc> pq;
    pq.push({0, S, 0, 0});
    while (!pq.empty()) {
        int n = pq.top().n;
        int k1 = pq.top().k1;
        int k2 = pq.top().k2;
        pq.pop();

        if (vis[n][k1][k2]) continue;
        vis[n][k1][k2] = 1;

        for (pii nb : nbs[n][0]) {
            if (dist[nb.FF][k1][k2] > dist[n][k1][k2] + nb.SS) {
                dist[nb.FF][k1][k2] = dist[n][k1][k2] + nb.SS;
                pq.push({dist[nb.FF][k1][k2], nb.FF, k1, k2});
            }
        }

        if (k1 < K1) {
            for (pii nb : nbs[n][1]) {
                if (dist[nb.FF][k1 + 1][k2] > dist[n][k1][k2] + nb.SS) {
                    dist[nb.FF][k1 + 1][k2] = dist[n][k1][k2] + nb.SS;
                    pq.push({dist[nb.FF][k1 + 1][k2], nb.FF, k1 + 1, k2});
                }
            }
        }

        if (k2 < K2) {
            for (pii nb : nbs[n][2]) {
                if (dist[nb.FF][k1][k2 + 1] > dist[n][k1][k2] + nb.SS) {
                    dist[nb.FF][k1][k2 + 1] = dist[n][k1][k2] + nb.SS;
                    pq.push({dist[nb.FF][k1][k2 + 1], nb.FF, k1, k2 + 1});
                }
            }
        }
    }

    if (dist[T][K1][K2] == LINF) cout << -1 << endl;
    else cout << dist[T][K1][K2] << endl;

    return 0;
} 