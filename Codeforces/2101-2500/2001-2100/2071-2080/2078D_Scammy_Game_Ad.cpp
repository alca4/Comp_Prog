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

const int MAXN = 40;
int N;
pii gates[MAXN][2], nextmult[MAXN][2];
ll score[MAXN][2];

void reset_tc() {
    for (int j = 0; j < 2; j++) for (int i = 1; i <= N; i++) {
        gates[i][j] = nextmult[i][j] = pii(0, 0);
        score[i][j] = 0;
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        char c1, c2;
        cin >> c1 >> gates[i][0].FF >> c2 >> gates[i][1].FF;
        if (c1 == 'x') gates[i][0].SS = 1;
        if (c2 == 'x') gates[i][1].SS = 1;
    }

    nextmult[N][0] = nextmult[N][1] = pii(INF, INF);
    for (int i = N - 1; i >= 1; i--) {
        for (int j = 0; j < 2; j++) {
            if (gates[i + 1][j].SS) nextmult[i][j] = pii(i + 1, -gates[i + 1][j].FF);
            else nextmult[i][j] = nextmult[i + 1][j];
        }
    }

    score[0][0] = score[0][1] = 1;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 2; j++) {
            // cout << nextmult[i][j].FF << " " << nextmult[i][j].SS << " ";
            if (gates[i][j].SS) score[i][j] = score[i - 1][j] * gates[i][j].FF;
            else score[i][j] = score[i - 1][j] + gates[i][j].FF;
        }
        // cout << endl;

        int go_left = 0;
        for (int j = i; j <= N; j++) {
            if (nextmult[j][0] != nextmult[j][1]) {
                if (nextmult[j][0] < nextmult[j][1]) go_left = 1;
                break;
            }
        }

        if (go_left) {
            // cout << "go left" << endl;
            score[i][0] += score[i][1] - score[i - 1][1];
            score[i][1] = score[i - 1][1];
        }
        else {
            // cout << "go right" << endl;
            score[i][1] += score[i][0] - score[i - 1][0];
            score[i][0] = score[i - 1][0];
        }
        // cout << score[i][0] << " " << score[i][1] << endl;
    }

    cout << score[N][0] + score[N][1] << endl;
    
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