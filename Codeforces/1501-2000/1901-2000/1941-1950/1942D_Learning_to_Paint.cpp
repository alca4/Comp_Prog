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

const int MAXN = 1010;
int N, K;
int arr[MAXN];
int cost[MAXN][MAXN];
vector<int> dp[MAXN];
int counter[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N - i + 1; j++) cost[i][i + j - 1] = 0;
    for (int i = 0; i <= N; i++) {
        arr[i] = 0;
        dp[i].clear();
    }
}

void solve() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N - i + 1; j++) {
            cin >> cost[i][i + j - 1];
        }
    }

    dp[0].pb(0);
    for (int i = 1; i <= N; i++) {
        dp[i].pb(cost[1][i]);
        if (i > 1) dp[i].pb(cost[2][i]);

        priority_queue<pii> duck;
        for (int j = 1; j <= i - 2; j++) {
            duck.push(pii(dp[j][counter[j]] + cost[j + 2][i], j));
            counter[j]++;
        }
        
        while (size(dp[i]) < 3 * K) {
            if (duck.empty()) break;
            pii n = duck.top();
            duck.pop();

            dp[i].pb(n.FF);
            if (counter[n.SS] < size(dp[n.SS])) 
                duck.push(pii(dp[n.SS][counter[n.SS]] + cost[n.SS + 2][i], n.SS));
            counter[n.SS]++;
        }

        for (int n2 : dp[i - 1]) dp[i].pb(n2);
        sort(dp[i].rbegin(), dp[i].rend());
        if (size(dp[i]) > K) dp[i].resize(K);

        // cout << "dee pee on " << i << endl;
        // for (int n : dp[i]) cout << n << " ";
        // cout << endl;

        for (int j = 1; j <= i - 2; j++) counter[j] = 0;
    }

    for (int i = 0; i < K; i++) cout << dp[N][i] << " ";
    cout << endl;

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