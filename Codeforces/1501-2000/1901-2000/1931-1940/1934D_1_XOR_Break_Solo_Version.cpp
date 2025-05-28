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

void reset_tc() {

}

void solve() {
    ll x, y;
    cin >> x >> y;

    ll x0 = x;
    vector<ll> ops;
    
    int fail = 0;
    // int just_have_room = 0;
    int haver = 0;
    int safe = 0;
    while (x != y) {
        int xlb = (x ? 63 - __builtin_clzll(x) : -1);
        int ylb = (y ? 63 - __builtin_clzll(y) : -1);
        // cout << x << " " << y << " " << xlb << " " << ylb << endl;

        if (xlb < ylb) {
            if (!safe || ops.empty()) {
                fail = 1;
                break;
            }
            else {
                // cout << safe << " " << size(ops) << endl;
                ops[0] |= (1ll << ylb);
                y &= ~(1ll << ylb);
            }
        }
        else if (xlb == ylb) {
            x &= ~(1ll << xlb);
            y &= ~(1ll << xlb);
            safe = 1;
        }
        else {
            // cout << (1ll << xlb) << endl;
            // cout << x << " " << ~(1ll << xlb) << endl;
            x &= ~(1ll << xlb);
            ops.pb(1ll << xlb);
            if (haver) safe = 1;
            haver = 1;
            // just_have_room = 1;
            // cout << x << " " << !(1ll << xlb) << endl;
        }
    }

    if (fail) cout << -1 << endl;
    else {
        cout << size(ops) << endl;
        cout << x0 << " ";
        for (ll n : ops) {
            x0 ^= n;
            cout << x0 << " ";
            // cout << n << " ";
        }
        cout << endl;
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