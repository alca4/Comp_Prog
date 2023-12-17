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

const int MAXN = 2010;
int N;
int arr[MAXN];
int dp[MAXN][MAXN];
pii pv[MAXN][MAXN];
vector<pii> range;
set<int> ints;
set<int> others;

void solve() {
    cin >> N;
    for (int i = 1; i <= 2 * N; i++) {
        cin >> arr[i];
        ints.insert(i);
    }

    int l = 1;
    for (int i = 2; i <= 2 * N; i++) {
        if (arr[i] > arr[l]) {
            range.pb({l, i - l});
            l = i;
        }
    }
    range.pb({l, 2 * N - l + 1});
    
    dp[0][0] = 1;
    for (int i = 0; i < range.size(); i++) {
        for (int j = 0; j <= N; j++) {
            if (range[i].SS + j <= N && dp[i][j]) {
                dp[i + 1][range[i].SS + j] = 1;
                pv[i + 1][range[i].SS + j] = pii(i, j);
            }
            if (dp[i][j]) {
                dp[i + 1][j] = 1;
                pv[i + 1][j] = pii(i, j);
            }
        }
    }

    // for (pii p : range) cout << p.FF << " " << p.SS << endl;

    if (!dp[range.size()][N]) cout << -1 << endl;
    else {
        int x = range.size(), y = N;
        for (int i = 1; i <= range.size(); i++) {
            if (dp[x][y]) {
                if (pv[x][y].SS != y) {
                    // cout << "range " << x << endl;
                    // cout << range[x - 1].FF << " " << range[x - 1].FF + range[x - 1].SS << endl;
                    for (int j = range[x - 1].FF; j < range[x - 1].FF + range[x - 1].SS; j++) {
                        // cout << j << " ";
                        others.insert(j);
                        ints.erase(j);
                    }
                }
                pii p = pv[x][y];
                // cout << x << " " << y << " to ";
                x = p.FF;
                y = p.SS;
                // cout << x << " " << y << endl;
            }
        }
        // cout << endl;
        for (auto n : others) cout << arr[n] << " ";
        cout << endl;

        for (auto n : ints) cout << arr[n] << " ";
        cout << endl;
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
    // T = "change";
    while (T--) solve();

    return 0;
} 