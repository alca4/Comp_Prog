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

Tooting Bec
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

struct DSU {
    vector<int> p, sz;

    DSU() {DSU(0);}
    DSU(int n) {
        p.resize(n + 1);
        sz.resize(n + 1);
        for (int i = 0; i <= n; i++) p[i] = i, sz[i] = 1;
    }

    int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
    int combine(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) return 0;

        if (sz[a] < sz[b]) swap(a, b);
        p[b] = a;
        sz[a] += sz[b];
        return 1;
    }
};

int N, M, ML;
int opening[MAXN];
int anses[MAXN];
bitset<MAXN> tester;
vector<int> ls[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        ls[i].clear();
    }

    for (int i = 0; i <= ML + 2; i++) opening[i] = anses[i] = 0;
}

void solve() {
    cin >> N >> M;
    ML = 0;
    for (int i = 1; i <= N; i++) {
        int l;
        cin >> l;

        ML = max(ML, l);
        
        for (int j = 1; j <= l; j++) {
            int n;
            cin >> n;
            ls[i].pb(n);
        }
    }

    DSU dsu(ML + 2);
    for (int i = 1; i <= N; i++) {
        for (int n : ls[i]) if (n <= ML + 2) tester[n] = 1;
        
        int n1 = -1, n2 = -1;
        for (int j = 0; j <= ML + 2; j++) {
            if (n1 == -1 && !tester[j]) n1 = j;
            else if (n2 == -1 && !tester[j]) n2 = j;
            if (n1 >= 0 && n2 >= 0) break;
        }
        tester = 0;

        dsu.combine(n1, n2);
        opening[n1]++;
        // cout << n1 << " " << n2 << endl;
    }

    for (int i = 0; i <= ML + 2; i++) {
        int rt = dsu.root(i);
        anses[rt] = max(anses[rt], i);
    }

    int always_can_do = 0;
    for (int i = 0; i <= ML + 2; i++) {
        if (opening[i] > 1) always_can_do = max(always_can_do, anses[dsu.root(i)]);
        if (opening[i]) always_can_do = max(always_can_do, i);
    }

    ll ans = 0;
    for (int i = 0; i <= min(M, ML + 2); i++) {
        // cout << max({i, anses[dsu.root(i)], always_can_do}) << " ";
        ans += max({i, anses[dsu.root(i)], always_can_do});
    }
    if (M >= ML + 2) ans += 1ll * M * (M + 1) / 2 - 1ll * (ML + 2) * (ML + 3) / 2;
    cout << ans << endl;
    reset_tc();
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