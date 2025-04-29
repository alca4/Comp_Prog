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
string str;
string alphabet = "abcdefghijklmnopqrstuvwxyz";

void reset_tc() {

}

void solve() {
    // cout << "New TC" << endl;
    cin >> str;
    str = '#' + str;
    int N = str.length() - 1;

    int fdiff = 0;
    for (int i = 1; i <= N / 2; i++) {
        if (str[i] != str[N + 1 - i]) {
            fdiff = i;
            break;
        }
    }

    if (fdiff == 0) {
        cout << 0 << endl;
        reset_tc();
        return;
    }

    map<char, int> cnt;
    for (int i = fdiff; i <= N + 1 - fdiff; i++) cnt[str[i]]++;

    map<char, int> lcnt;
    int lborder = 0;
    for (int i = fdiff; i <= N / 2; i++) {
        lcnt[str[i]]++;
        if (lcnt[str[i]] > cnt[str[i]] / 2) {
            lborder = i;
            break;
        }
    }

    int rborder = 0;
    map<char, int> rcnt;
    for (int i = N + 1 - fdiff; i >= N / 2 + 1; i--) {
        rcnt[str[i]]++;
        if (rcnt[str[i]] > cnt[str[i]] / 2) {
            rborder = i;
            break;
        }
    }

    // cout << lborder << " " << rborder << endl;
    if (lborder == 0 && rborder == 0) {
        int ldiff = 0;
        for (int i = N / 2; i >= fdiff; i--) {
            if (str[i] != str[N + 1 - i]) {
                ldiff = i;
                break;
            }
        }
        // cout << fdiff << " " << ldiff << endl;
        cout << ldiff - fdiff + 1 << endl;
    }
    else {
        cout << min(rborder - fdiff + 1, (N + 1 - fdiff) - lborder + 1) << endl;
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