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

#define ll long long
#define ld long double
#define ull unsigned ll

#define endl "\n"
#define EPS 1e-9

#define sz(v) (int) v.size()
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
// #define cout cerr

ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;

#define add(a, b) ((a + b) > MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) > 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) ((a * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N;
ll lb[MAXN], ub[MAXN], v[MAXN];
vi nbs[MAXN];
ll incrementer = 0;

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        lb[i] = ub[i] = v[i] = 0;
        nbs[i].clear();
    }
    incrementer = 0;
}

void DP(int a, int p) {
    for (int nb : nbs[a]) if (nb != p) DP(nb, a);

    ll maxnb = 0;
    for (int nb : nbs[a]) if (nb != p) maxnb = max(maxnb, v[nb]);

    v[a] = min(ub[a], max(lb[a], maxnb));

    ll new_inc = 0;
    for (int nb : nbs[a]) new_inc += max(0ll, v[nb] - v[a]);
    // for (int nb : nbs[a]) if (nb != p) lb[nb] += inc[a] - inc[nb];

    // cout << a << " inc: " << new_inc << endl;
    // cout << a << " is " << lb[a] << endl;
    // cout << "children are: " << endl;
    // for (int nb : nbs[a]) if (nb != p) cout << nb << ": " << lb[nb] << " ";
    // cout << endl;
    // cout << endl;
    
    incrementer += new_inc;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> lb[i] >> ub[i];
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DP(1, 0);
    cout << v[1] + incrementer << endl;

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