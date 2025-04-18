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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
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
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N, M, H;
vector<pll> nbs[MAXN];
ll dist1[MAXN * 2];
ll distN[MAXN * 2];
int vis[MAXN * 2];
bool horses[MAXN];

void solve() {
    cin >> N >> M >> H;
    for (int i = 1; i <= H; i++) {
        int a;
        cin >> a;
        horses[a] = 1;
    }
    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        nbs[a].pb(pll(b, c));
        nbs[b].pb(pll(a, c));
    }

    for (int i = 1; i <= 2 * N; i++) dist1[i] = LINF;
    dist1[1] = 0;
    priority_queue<pll> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        ll dist = -pq.top().FF;
        int n = pq.top().SS;
        bool hors = (pq.top().SS > N) || horses[(n - 1) % N + 1];
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (pll nb : nbs[(n - 1) % N + 1]) {
            int nv = nb.FF + (hors ? N : 0);
            ll d = (hors ? nb.SS / 2 : nb.SS);
            if (dist + d < dist1[nv]) {
                dist1[nv] = dist + d;
                pq.push(pll(-(dist + d), nv));
            }
        }
    }

    for (int i = 1; i <= 2 * N; i++) vis[i] = 0;
    for (int i = 1; i <= 2 * N; i++) distN[i] = LINF;
    distN[N] = 0;
    pq.push({0, N});
    while (!pq.empty()) {
        ll dist = -pq.top().FF;
        int n = pq.top().SS;
        bool hors = (pq.top().SS > N) || horses[(n - 1) % N + 1];
        pq.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        for (pll nb : nbs[(n - 1) % N + 1]) {
            int nv = nb.FF + (hors ? N : 0);
            ll d = (hors ? nb.SS / 2 : nb.SS);
            if (dist + d < distN[nv]) {
                distN[nv] = dist + d;
                pq.push(pll(-(dist + d), nv));
            }
        }
    }

    // for (int i = 1; i <= 2 * N; i++) cout << dist1[i] << endl;
    // for (int i = 1; i <= 2 * N; i++) cout << distN[i] << endl;

    ll ans = LINF;
    for (int i = 1; i <= N; i++) {
        mineq(ans, max(min(dist1[i], dist1[i + N]), 
                       min(distN[i], distN[i + N])));
    }

    cout << (ans == LINF ? -1 : ans) << endl;

    for (int i = 1; i <= 2 * N; i++) dist1[i] = distN[i] = vis[i] = 0;
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        horses[i] = 0;
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 