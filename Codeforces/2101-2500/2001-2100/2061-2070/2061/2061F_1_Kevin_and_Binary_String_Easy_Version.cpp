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

#define size(v) (int) v.size()
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
typedef vector<pii> vpii;

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((a * b) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 64; i++) {
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

const int MAXN = 0;
int N;
string s, t;

void reset_tc() {

}

void solve() {
    cin >> s >> t;
    N = s.length();
    
    int si = 0;
    int ti = 0;

    int yay = 1;
    int ops = 0;
    while (si < N) {
        if (si != 0 && s[si] != t[ti]) {
            // cout << "trigger1 duck at " << si << endl;
            yay = 0;
        }

        char cur = t[ti];
        while (ti < N && t[ti] == cur) ti++;

        int si0 = si;
        int need = ti - si;
        int have = 0;
        int tops = 0;
        while (si < N && have < need) {
            if (s[si] == cur) have++;
            if (si != si0 && s[si] != s[si - 1]) tops++;
            si++;
        }
        ops += (tops + 1) / 2;

        if (have < need) {
            yay = 0;
            // cout << "trigger2 duck" << endl;
        }
        if (si < N && s[si] == s[si - 1]) {
            // cout << "trigger3 duck" << endl;
            yay = 0;
        }

        while (ti < si) {
            if (t[ti] == cur) yay = 0;
            ti++;
        }
        // cout << "at " << si << endl;
    }

    if (yay) cout << ops << endl;
    else cout << -1 << endl;

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