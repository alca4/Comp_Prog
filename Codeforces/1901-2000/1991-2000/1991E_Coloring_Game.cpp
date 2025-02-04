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
// #define endl "\n"
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

const int MAXN = 10010;
int N, M;
vector<int> nbs[MAXN];
int col[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        col[i] = 0;
        nbs[i].clear();
    }
}

int DFS(int a, int p) {
    col[a] = 3 - col[p];

    for (int nb : nbs[a]) if (nb != p) {
        if (col[nb]) {
            if (col[nb] == col[a]) return 1;
        }
        else if (DFS(nb, a)) return 1;
    }

    return 0;
}

void solve_alice() {
    for (int i = 1; i <= N; i++) {
        cout << 1 << " " << 2 << endl;
        int a, b;
        cin >> a >> b;
    }
}

void solve_bob() {
    vector<int> ones, twos;
    for (int i = 1; i <= N; i++) {
        if (col[i] == 1) ones.pb(i);
        else twos.pb(i);
    }

    for (int i = 1; i <= N; i++) {
        int a, b;
        cin >> a >> b;

        if (a > b) swap(a, b);

        if (ones.size()) {
            if (a == 1) {
                cout << ones.back() << " " << 1 << endl;
                ones.pop_back();
            }
            else if (twos.size()) {
                assert(a == 2 && b == 3);
                cout << twos.back() << " " << 2 << endl;
                twos.pop_back();
            }
            else {
                assert(a == 2 && b == 3);
                cout << ones.back() << " " << 3 << endl;
                ones.pop_back();
            }
        }
        else {
            if (b == 3) {
                cout << twos.back() << " " << 3 << endl;
                twos.pop_back();
            }
            else {
                cout << twos.back() << " " << 2 << endl;
                twos.pop_back();
            }
        }
    }
}

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    col[0] = 1;

    // cout << "maybe cycle?" << endl;
    // for (int i = 1; i <= N; i++) cout << dfs_order[i] << " ";
    // cout << endl;

    if (DFS(1, 0)) {
        cout << "Alice" << endl;
        solve_alice();
    }
    else {
        cout << "Bob" << endl;
        solve_bob();
    }

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