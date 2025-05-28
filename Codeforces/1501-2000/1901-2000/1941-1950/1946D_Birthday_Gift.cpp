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

const int MAXN = 100010;
int N, K;
int arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    K++;

    set<pii> rngs;
    for (int i = 1; i <= N; i++) rngs.insert(pii(i, i));

    int ans = -1;
    for (int i = 30; i >= 0; i--) {
        int cnt = 0;
        for (int j = 1; j <= N; j++) cnt ^= (arr[j] & (1 << i)) >> i;

        if (cnt) {
            if (!(K & (1 << i))) break;
            continue;
        }

        if (K & (1 << i)) {
            // cout << "triggered on " << i << endl;
            set<pii> buddy = rngs;
            // for (pii p : buddy) cout << p.FF << " " << p.SS << endl;

            int lguy = 0;
            for (int j = 1; j <= N; j++) {
                if (arr[j] & (1 << i)) {
                    if (lguy == 0) lguy = j;
                    else {
                        buddy.insert(pii(lguy, j));
                        lguy = 0;
                    }
                }
            }

            int tans = 0;
            while (size(buddy) > 1) {
                pii p1 = *buddy.begin();
                buddy.erase(buddy.begin());
                pii p2 = *buddy.begin();
                buddy.erase(buddy.begin());
        
                if (p2.FF <= p1.SS) buddy.insert(pii(p1.FF, max(p1.SS, p2.SS)));
                else {
                    buddy.insert(p2);
                    tans++;
                }
            }
            if (size(buddy) == 1) tans++;

            ans = max(ans, tans);
        }
        else {
            int lguy = 0;
            for (int j = 1; j <= N; j++) {
                if (arr[j] & (1 << i)) {
                    if (lguy == 0) lguy = j;
                    else {
                        rngs.insert(pii(lguy, j));
                        // cout << "at " << i << " " << lguy << " " << j << endl;
                        lguy = 0;
                    }
                }
            }
        }
    }

    // for (pii p : rngs) cout << p.FF << " " << p.SS << endl;

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