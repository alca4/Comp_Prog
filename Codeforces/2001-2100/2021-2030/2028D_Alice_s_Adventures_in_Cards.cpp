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
int N;
string players = "#qkj";
int values[MAXN][4];
pii seen[4];
pii from[MAXN];

void reset_tc() {
    for (int j = 1; j <= 3; j++) {
        seen[j] = pii(0, 0);
        for (int i = 1; i <= N; i++) values[i][j] = 0;
    }
    for (int i = 1; i <= N; i++) from[i] = pii(0, 0);
}

void solve() {
    cin >> N;
    for (int j = 1; j <= 3; j++) {
        for (int i = 1; i <= N; i++) cin >> values[i][j];
    }

    for (int j = 1; j <= 3; j++) seen[j] = pii(values[1][j], 1);

    for (int i = 2; i <= N; i++) {
        int ok = 0;
        for (int j = 1; j <= 3; j++) if (values[i][j] < seen[j].FF) {
            ok = 1;
            from[i] = pii(seen[j].SS, j);
            // cout << i << " from " << seen[j].SS << " " << players[j] << endl;
        }

        if (!ok) continue;

        for (int j = 1; j <= 3; j++) {
            seen[j] = max(seen[j], pii(values[i][j], i));
        }
    }

    if (from[N] == pii(0, 0)) cout << "NO" << endl;
    else {
        cout << "YES" << endl;
        vector<pii> ops;
        int at = N;
        while (at != 1) {
            ops.pb(from[at]);
            at = from[at].FF;
        }

        reverse(ops.begin(), ops.end());

        cout << ops.size() << endl;
        for (int i = 0; i < ops.size() - 1; i++) 
            cout << players[ops[i].SS] << " " << ops[i + 1].FF << endl;
        
        cout << players[ops.back().SS] << " " << N << endl;
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