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
int N, M;
int c[MAXN], s[MAXN], f[MAXN];
vector<int> nbs[MAXN];
int have[MAXN];
int have2[MAXN];
int vis[MAXN];
vector<int> new_nb[MAXN];

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> c[i];
    for (int i = 1; i <= N; i++) cin >> s[i];
    for (int i = 1; i <= N; i++) cin >> f[i];

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    queue<int> bfs;
    bfs.push(1);
    while (!bfs.empty()) {
        int n = bfs.front();
        bfs.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        have[s[n]]++;
        if (have[s[n]] == 1) {
            for (int nb : new_nb[s[n]]) bfs.push(nb);
            new_nb[s[n]].clear();
        }
        for (int nb : nbs[n]) {
            if (!have[c[nb]]) new_nb[c[nb]].pb(nb);
            else bfs.push(nb);
        }
    }

    // for (int i = 1; i <= N; i++) cout << have[i] << " ";
    // cout << endl;

    int ok = 1;
    for (int i = 1; i <= N; i++) {
        if (!vis[i] && s[i] != f[i]) ok = 0;
        vis[i] = 1 - vis[i];
        new_nb[i].clear();
    }

    bfs.push(1);
    while (!bfs.empty()) {
        int n = bfs.front();
        bfs.pop();

        if (vis[n]) continue;
        vis[n] = 1;

        have2[f[n]]++;
        if (have2[f[n]] == 1) {
            for (int nb : new_nb[f[n]]) bfs.push(nb);
            new_nb[f[n]].clear();
        }
        for (int nb : nbs[n]) {
            if (!have2[c[nb]] && c[nb] != f[nb]) new_nb[c[nb]].pb(nb);
            else bfs.push(nb);
        }
    }

    int ok2 = 1;
    for (int i = 1; i <= N; i++) {
        if (!vis[i] && s[i] != f[i]) ok2 = 0;
        vis[i] = 0;
    }

    // cout << ok << " " << ok2 << endl;

    if (ok && ok2) cout << "YES" << endl;
    else cout << "NO" << endl;

    for (int i = 1; i <= N; i++) {
        c[i] = s[i] = f[i] = have[i] = have2[i] = vis[i] = 0;
        nbs[i].clear();
        new_nb[i].clear();
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