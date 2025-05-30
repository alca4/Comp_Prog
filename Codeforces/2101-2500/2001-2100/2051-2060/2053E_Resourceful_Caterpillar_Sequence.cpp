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
int N;
vector<int> nbs[MAXN];
int dist[MAXN];
int sz[MAXN];
ll z[MAXN];
ll o[MAXN];
ll tp[MAXN];

void DFS(int a, int p) {
    for (int nb : nbs[a]) if (nb != p) {
        dist[nb] = min(dist[nb], dist[a] + 1);

        DFS(nb, a);

        dist[a] = min(dist[a], dist[nb] + 1);

        z[a] += z[nb];
        o[a] += o[nb];
        tp[a] += tp[nb];
        sz[a] += sz[nb];
    }

    if (dist[a] == 0) z[a]++;
    else if (dist[a] == 1) o[a]++;
    else tp[a]++;
    sz[a]++;

    // cout << a << ": " << z[a] << " " << o[a] << " " << tp[a] << endl;
}

ll DFS2(int a, int p) {
    ll ans = 0;

    if (dist[a] == 0) {
        ans += o[1] + tp[1];
        // cout << a << " is leaf, so " << o[1] + tp[1] << endl;
    }

    if (dist[a] > 0 && dist[p] == 1) {
        ans += tp[1] - tp[a];
        // cout << a << " can go up to " << p << " with " << tp[1] - tp[a] << endl;
    }

    for (int nb : nbs[a]) if (nb != p) {
        if (dist[a] > 0 && dist[nb] == 1) {
            // cout << a << " can go down to " << nb << " with " << tp[nb] << endl;
            ans += tp[nb];
        }
        
        ans += DFS2(nb, a);
    }

    return ans;
}

void solve() {
    cin >> N;
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) {
        if (nbs[i].size() > 1) dist[i] = INF;
    }

    DFS(1, 0);

    cout << DFS2(1, 0) << endl;

    for (int i = 1; i <= N; i++) {
        dist[i] = 0;
        z[i] = o[i] = tp[i] = 0;
        nbs[i].clear();
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