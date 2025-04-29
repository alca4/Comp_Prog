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

const int MAXN = 200010;
int N, K;
int a[MAXN], b[MAXN];
int ta[MAXN], tb[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) a[i] = b[i] = ta[i] = tb[i] = 0;
}

/*
0 7 3 1 0 0 0 1
7 0 0 0 1 3 5 0


*/

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];

    int ans = 0;
    int lb = 1, ub = N;
    while (lb <= ub) {
        int mid = (lb + ub) / 2;
        // cout << mid << endl;

        for (int i = 1; i <= N; i++) ta[i] = a[i], tb[i] = b[i];

        set<int> indices;
        for (int i = N; i >= 1; i--) {
            indices.insert(i);
            for (int j = 1; j <= mid; j++) {
                if (indices.empty()) break;

                int nid = *indices.begin(); 
                if (i + mid <= nid) break;
                int c = min(ta[i], tb[nid]);
                ta[i] -= c;
                tb[nid] -= c;

                if (ta[i] == 0) break;
                else indices.erase(nid);
            }
        }

        int ai = N, bi = 1;
        while (bi + N - ai < mid) {
            if (ta[ai] && tb[bi]) {
                int c = min(ta[ai], tb[bi]);
                ta[ai] -= c;
                tb[bi] -= c;
            }
            if (ta[ai]) bi++;
            else ai--;
        }

        int has_pos = 0;
        for (int i = 1; i <= N; i++) if (ta[i] > 0) has_pos = 1;
        // for (int i = 1; i <= N; i++) cout << ta[i] << " ";
        // cout << endl;
        // for (int i = 1; i <= N; i++) cout << tb[i] << " ";
        // cout << endl;

        if (has_pos) lb = mid + 1;
        else {
            ans = mid;
            ub = mid - 1;
        }
    }

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