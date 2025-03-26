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
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
#define endl "\n"
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 1510;
int N, M, L;
int grid[MAXN][MAXN];
int score[MAXN][MAXN][2];
int prefsum[MAXN][MAXN];
int prefsum2[MAXN][MAXN];
int arr[MAXN];

void reset_tc() {
    for (int i = 1; i <= L; i++) arr[i] = 0;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
        score[i][j][0] = score[i][j][1] = grid[i][j] = 0;
    }
}

void solve() {
    cin >> L >> N >> M;
    for (int i = 1; i <= L; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> grid[i][j];

    int win = 0;
    for (int l = L; l >= 1; l--) {
        for (int i = N; i >= 1; i--) for (int j = M; j >= 1; j--) {
            prefsum2[i][j] = prefsum2[i + 1][j] + prefsum2[i][j + 1] - prefsum2[i + 1][j + 1];
            if (grid[i][j] == arr[l + 1]) prefsum2[i][j]++;
        }

        for (int i = N; i >= 1; i--) for (int j = M; j >= 1; j--) {
            prefsum[i][j] = prefsum[i + 1][j] + prefsum[i][j + 1] - prefsum[i + 1][j + 1];
            if (score[i][j][0]) prefsum[i][j]++;
        }

        // if (l == 2) cout << prefsum[3][3] << " " << presence[3][3][3] << endl;

        for (int i = N; i >= 1; i--) for (int j = M; j >= 1; j--) if (grid[i][j] == arr[l]) {
            if (prefsum[i + 1][j + 1] == 0 || prefsum2[i][j] == 0) score[i][j][1]++;
        }

        
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                // cout << score[i][j][1] << " ";
                score[i][j][0] = score[i][j][1];
                score[i][j][1] = 0;
                if (score[i][j][0] && l == 1) win = 1;
                
                prefsum[i][j] = prefsum2[i][j] = 0;
            }
            // cout << endl;
        }
        // cout << endl;
    }

    // cout << presence[3][3][3] << endl;

    cout << (win ? 'T' : 'N') << endl;
    
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