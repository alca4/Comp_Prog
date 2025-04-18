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
ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) ((a + b) >= MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) >= 0 ? a - b : a + MOD - b)
#define mult(a, b) ((1ll * (a) * (b)) % MOD)
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
#define divide(a, b) ((1ll * (a) * power(b, MOD - 2)) % MOD)

#define maxeq(x, y) if (x < y) x = y
#define mineq(x, y) if (x > y) x = y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;

struct Comb {
    vl fact, factinv;
    vector<vl> stirling;
    /* 
    stirling numbers of the first kind
    s[i][j] = jth coefficient of x risepow i
    s[i][j] = number of permutations length i with j cycles
    */
    vector<vl> stirling2;
    /*
    stirling numbers of the second kind
    s2[i][j] = jth coefficient of x fallpow i
    s2[i][j] = number of ways to partition i elements into j subsets
    */

    Comb(int x) {
        fact.resize(x + 1);
        factinv.resize(x + 1);
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
    }

    void gen_stirling(int i, int j) {
        stirling.resize(i + 1);
        for (auto& n : stirling) n.resize(j + 1);
        stirling[0][0] = 1;
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n && k)
                stirling[n][k] = add(mult(sub(0, n - 1), stirling[n - 1][k]), stirling[n - 1][k - 1]);
        }
    }


    void gen_stirling2(int i, int j) {
        stirling2.resize(i + 1);
        for (auto& n : stirling2) n.resize(j + 1);
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n == k) stirling2[n][k] = 1;
            if (n && k) 
                stirling2[n][k] = add(stirling2[n - 1][k - 1], mult(k, stirling2[n - 1][k]));
        }
    }

    ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }

    ll fallpow(int a, int b) {
        return mult(fact[a], factinv[a - b]);
    }

    ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};

int N;
int arr[MAXN];
int freq[MAXN];
int pow2[MAXN];

vector<int> dp[MAXN];
Comb c = Comb(MAXN);

void reset_tc() {
    for (int i = 0; i <= N; i++) {
        freq[i] = arr[i] = 0;
        dp[i].clear();
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }

    int prefmin = freq[0];
    dp[0].pb(0);
    for (int i = 1; i <= freq[0]; i++) dp[0].pb(c.choose(freq[0], i));
    
    for (int i = 1; i <= N; i++) {
        dp[i].resize(min(prefmin, freq[i]) + 1);
        int guys = 0;
        for (int j = 1; j <= prefmin; j++) addeq(guys, dp[i - 1][j]);
        int guys2 = 0;
        for (int j = 2; j <= freq[i]; j++) addeq(guys2, c.choose(freq[i], j));

        for (int j = 1; j <= min(prefmin, freq[i]); j++) {
            dp[i][j] = mult(guys, c.choose(freq[i], j));
            subeq(guys, dp[i - 1][j]);

            if (j < freq[i]) {
                addeq(dp[i][j], mult(guys2, dp[i - 1][j]));
                subeq(guys2, c.choose(freq[i], j + 1));
            }
        }

        mineq(prefmin, freq[i]);
    }

    int ans = 0;
    int prevseen = 0;
    for (int i = 0; i <= N; i++) {
        prevseen += freq[i];
        for (int j = 1; j < size(dp[i]); j++) 
            addeq(ans, mult(dp[i][j], mult(j, pow2[N - prevseen])));
    }
    // cout << "ans is: " << endl;
    cout << ans << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    pow2[0] = 1;
    for (int i = 1; i <= 200000; i++) pow2[i] = mult(pow2[i - 1], 2);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 

/*
1: 0
1: 0
0: 1
2: 0 0
2: 0 1
2: 0 1
3: 0 0 1

0 1
0 1
1 1
0 0 1
0 1 1
0 1 1
0 0 1 1
*/