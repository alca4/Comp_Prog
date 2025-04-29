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

// #define endl "\n"
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

const int MAXN = 0;
int N;

/*
 1001
 0111
10000


 1101
 0111
10100


 1011
 1111
11010
*/

void reset_tc() {

}

void solve() {
    int q1 = 0;
    for (int i = 0; i <= 28; i += 2) q1 |= (1 << i);
    cout << q1 << endl;
    int a1;
    cin >> a1;

    int q2 = 0;
    for (int i = 1; i <= 29; i += 2) q2 |= (1 << i);
    cout << q2 << endl;
    int a2;
    cin >> a2;

    int f1 = 0;
    int f2 = 0;
    for (int i = 29; i >= 1; i -= 2) {
        int ta1 = a1 >> i;

        if (ta1 & 1) {
            if (ta1 & 2) {
                // cout << "double pushing " << i << endl;
                f1 |= 1 << i;
                f2 |= 1 << i;
            }
        }
        else {
            // cout << "pushing " << i << endl;
            f1 |= 1 << i;
        }
    }

    for (int i = 28; i >= 0; i -= 2) {
        int ta2 = a2 >> i;

        if ((ta2 & 1) ^ (i == 0)) {
            if (ta2 & 2) {
                // cout << "double pushing " << i << endl;
                f1 |= 1 << i;
                f2 |= 1 << i;
            }
        }
        else {
            // cout << "pushing " << i << endl;
            f1 |= 1 << i;
        }
    }

    cout << "!" << endl;
    int m;
    cin >> m;
    cout << (m | f1) + (m | f2) << endl;

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