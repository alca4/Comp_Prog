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

ll add(const ll& a, const ll& b) {
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) {
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
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 50010;
const int MAXA = 700;
int arr[MAXN];
vector<int> twins[MAXN + MAXA];
vector<int> nbs[MAXN + MAXA];
int vis[MAXN + MAXA];
int dist[MAXA][MAXN];
int N, Q;

void BFS(int a) {
    deque<pii> search;
    search.pb({a, 0});
    dist[a - N][a] = 0;
    while (!search.empty()) {
        int n = search.front().FF;
        int w = search.front().SS;
        search.pop_front();

        if (vis[n]) continue;
        vis[n] = 1;

        for (int twin : twins[n]) {
            if (dist[a - N][twin] > dist[a - N][n]) {
                dist[a - N][twin] = dist[a - N][n];
                search.push_front({twin, w});
            }
        }

        for (int nb : nbs[n]) {
            if (dist[a - N][nb] > dist[a - N][n] + 1) {
                dist[a - N][nb] = dist[a - N][n] + 1;
                search.push_back({nb, w + 1});
            }
        }
    }
}

void solve() {
    string str;
    cin >> str;
    N = str.length();

    for (int i = 1; i < N; i++) {
        arr[i] = (str[i] - 'a') * 26 + (str[i - 1] - 'a');
        nbs[i].pb(N + arr[i]);
        twins[N + arr[i]].pb(i);
    }

    for (int i = 2; i < N; i++) {
        nbs[i].pb(i - 1);
        nbs[i - 1].pb(i);
    }

    for (int i = 0; i < 676; i++) {
        for (int j = 1; j < N + 676; j++) dist[i][j] = INF;
        for (int j = 1; j < N + 676; j++) vis[j] = 0;
        BFS(N + i);
    }

    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);

        int ans = b - a;
        for (int i = 0; i < 676; i++) {
            ans = min(ans, dist[i][a] + dist[i][b] + 1);
        }
        cout << ans << endl;
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    while (T--) solve();

    return 0;
} 