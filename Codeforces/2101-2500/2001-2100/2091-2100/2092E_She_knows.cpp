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

const int dx4[4] = {0, 1, 0, -1};
const int dy4[4] = {1, 0, -1, 0};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N, M, K;
int a[MAXN], b[MAXN], c[MAXN];
int u[MAXN], l[MAXN], d[MAXN], r[MAXN];

void reset_tc() {
    for (int i = 1; i <= K; i++) a[i] = b[i] = c[i] = 0;
}

void solve() {
    cin >> N >> M >> K;
    int border_town = 0;
    int border_sum = 0;
    for (int i = 1; i <= K; i++) {
        cin >> a[i] >> b[i] >> c[i];

        int bt0 = border_town;
        if (a[i] == 1 && 1 < b[i] && b[i] < M) border_town++;
        if (a[i] == N && 1 < b[i] && b[i] < M) border_town++;
        if (b[i] == 1 && 1 < a[i] && a[i] < N) border_town++;
        if (b[i] == M && 1 < a[i] && a[i] < N) border_town++;
        if (bt0 != border_town) border_sum += c[i];
    }

    if (border_town == (N - 2 + M - 2) * 2) {
        if (border_sum % 2) cout << 0 << endl;
        else cout << power(2, 1ll * N * M - K) << endl;
    }
    else cout << power(2, 1ll * N * M - K - 1) << endl;

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