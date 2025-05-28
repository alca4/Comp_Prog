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
ll MOD = 1000000007;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((1ll * a * b) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 64; i++) {
        if (b & 1ll) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) ((1ll * a * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 5010;
int N, L, K;
int guys[MAXN];
int receiver[MAXN];
int aah[MAXN];
int modinverse[MAXN];

void reset_tc() {
    for (int j = 0; j < N; j++) guys[j] = receiver[j] = aah[j] = 0;
}

void solve() {
    cin >> N >> L >> K;
    
    receiver[N - 1] = 1;
    for (int i = 0; i < L; i++) {
        int benefits = 0;
        for (int j = 0; j < N; j++) if (receiver[j]) {
            for (int k = 0; k < (L - i) % N; k++) {
                addeq(aah[(j + k + 1) % N], mult(receiver[j], modinverse[L - i]));
            }
            addeq(benefits, mult(receiver[j], mult((L - i) / N, modinverse[L - i])));
        }

        for (int j = 0; j < N; j++) {
            addeq(guys[j], receiver[j]);
            receiver[j] = add(aah[j], benefits);
            aah[j] = 0;
        }
    }

    subeq(guys[N - 1], 1);
    for (int j = 0; j < N; j++) cout << add(guys[j], receiver[j]) << " ";
    cout << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 5000; i >= 1; i--) modinverse[i] = divide(1, i);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 