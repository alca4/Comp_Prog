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

#define sz(v) (int) v.size()
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

#define add(a, b) ((a + b) > MOD ? a + b - MOD : a + b)
#define sub(a, b) ((a - b) > 0 ? a - b : a + MOD - b)
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

const int MAXN = 100010;
int N, K;
int banhammer[MAXN][3];
int cur_guy[2][MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        banhammer[i][0] = banhammer[i][1] = banhammer[i][2] = 0;
        cur_guy[0][i] = cur_guy[1][i] = 0;
    }
}

void solve() {
    cin >> N >> K;

    if (K == 1 && N == 1) {
        cout << "YES" << endl;
        cout << 1 << endl;
    }
    else {
        int nfac = INF;
        if (N <= 10) {
            nfac = 1;
            for (int i = 1; i <= N; i++) nfac *= i;
        }

        if ((K % 2 && (N % 2) == 0) || K > nfac || K == nfac - 1 || K == 1) cout << "NO" << endl;
        else {
            cout << "YES" << endl;

            if (K % 2 && N % 2) {
                for (int i = 1; i <= N; i++) banhammer[i][0] = i;
                for (int i = 1; i <= N / 2; i++) banhammer[i][1] = N + 1 - 2 * i;
                int tv = N;
                for (int i = N / 2 + 1; i <= N; i++) {
                    banhammer[i][1] = tv;
                    tv -= 2;
                }
                for (int i = 1; i <= N / 2; i++) banhammer[i][2] = i + (N + 1) / 2;
                for (int i = N / 2 + 1; i <= N; i++) banhammer[i][2] = i - N / 2;

                for (int j = 0; j < 3; j++) {
                    for (int i = 1; i <= N; i++) cout << banhammer[i][j] << " ";
                    cout << endl;
                }
                K -= 3;
            }

            for (int i = 1; i <= N; i++) cur_guy[0][i] = i;
            do {
                for (int i = 1; i <= N; i++) cur_guy[1][i] = N + 1 - cur_guy[0][i];

                bool can_use = 1;
                for (int j = 0; j < 3; j++) for (int k = 0; k < 2; k++) {
                    bool tmp = 1;
                    for (int i = 1; i <= N; i++) if (cur_guy[k][i] != banhammer[i][j]) tmp = 0;
                    if (tmp) can_use = 0;
                }

                if (K >= 2 && can_use) {
                    for (int i = 1; i <= N; i++) cout << cur_guy[0][i] << " ";
                    cout << endl;
                    for (int i = 1; i <= N; i++) cout << cur_guy[1][i] << " ";
                    cout << endl;

                    K -= 2;
                }
            } while (K > 0 && next_permutation(cur_guy[0] + 1, cur_guy[0] + 1 + N));
        }
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

/*
1 2 3 4 5
4 2 5 3 1
4 5 1 2 3

1 2 3 4 5 6 7 8 9
8 6 4 2 9 7 5 3 1
6 7 8 9 1 2 3 4 5

9 1 2 3 4 5 6 7 8
1 9 8 7 6 5 4 3 2

9 8 7 6 5 4 3 2 1
1 3 5 7 9 2 4 6 8
5 4 3 2 1 9 8 7 6

1 2 3 4
3 1 4 2


*/