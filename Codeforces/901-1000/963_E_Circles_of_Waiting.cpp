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
ll MOD = 1000000007;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 110;
const int DELTA = 51;
int N;

int R, a, b, c, d, s;
int C;

int grid[MAXN][MAXN];
vector<int> dp[MAXN][MAXN];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int p[4];

int sol[MAXN];
vector<int> gauss[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> R >> a >> b >> c >> d;
    s = add(add(a, b), add(c, d));

    p[2] = divide(a, s);
    p[3] = divide(b, s);
    p[0] = divide(c, s);
    p[1] = divide(d, s);

    for (int i = -R - 1; i <= R + 1; i++) for (int j = -R - 1; j <= R + 1; j++) {
        dp[i + DELTA][j + DELTA].resize(2 * R + 2);
    }
    
    for (int i = -R; i <= R; i++) for (int j = -R; j <= R; j++) {
        if (i * i + j * j <= R * R) {
            dp[i + DELTA][j + DELTA][i + R + 1] = 1;
            break;
        }
    }
    
    for (int j = -R; j <= R; j++) for (int i = -R; i <= R; i++) {
        if (i * i + j * j <= R * R && i * i + (j + 1) * (j + 1) <= R * R) {
            vector<int> aah = dp[i + DELTA][j + DELTA];
            for (int d = 0; d < 3; d++) {
                int x = i + DELTA + dx[d];
                int y = j + DELTA + dy[d];

                for (int k = 0; k <= 2 * R + 1; k++) {
                    subeq(aah[k], mult(dp[x][y][k], p[d]));
                }
            }
            subeq(aah[0], 1);

            int x = i + DELTA;
            int y = j + DELTA + 1;

            for (int k = 0; k <= 2 * R + 1; k++) {
                diveq(aah[k], p[3]);
            }
            dp[x][y] = aah;
        }
    }

    // for (int j = -R; j <= R; j++) for (int i = -R; i <= R; i++) {
    //     if (i * i + j * j <= R) {
    //         cout << i << " " << j << endl;
    //         for (int k = 0; k <= 2 * R + 1; k++) cout << dp[i + DELTA][j + DELTA][k] << " ";
    //         cout << endl;
    //     }
    // }
    // cout << endl;

    for (int i = -R; i <= R; i++) for (int j = R; j >= -R; j--) {
        if (i * i + j * j <= R * R) {
            gauss[i + R] = dp[i + DELTA][j + DELTA];
            for (int d = 0; d < 4; d++) {
                int x = i + DELTA + dx[d];
                int y = j + DELTA + dy[d];

                for (int k = 0; k <= 2 * R + 1; k++) {
                    subeq(gauss[i + R][k], mult(dp[x][y][k], p[d]));
                }
            }
            subeq(gauss[i + R][0], 1);

            gauss[i + R].pb(sub(0, gauss[i + R][0]));
            break;
        }
    }

    // for (int i = 0; i <= 2 * R; i++) {
    //     for (int j = 1; j <= 2 * R + 2; j++) {
    //         cout << gauss[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    // cout << endl;

    int m = 0, n = 1;
    while (m <= 2 * R && n <= 2 * R + 1) {
        int best = m;
        for (int k = m; k <= 2 * R; k++) {
            if (gauss[k][n] > gauss[best][n]) best = k;
        }
        if (best) {
            for (int k = m + 1; k <= 2 * R; k++) {
                int r = divide(gauss[k][n], gauss[m][n]);

                gauss[k][n] = 0;
                for (int j = n + 1; j <= 2 * R + 2; j++) {
                    subeq(gauss[k][j], mult(gauss[m][j], r));
                }
            }
            m++;
        }
        n++;
    }

    // for (int i = 0; i <= 2 * R; i++) {
    //     for (int j = 1; j <= 2 * R + 2; j++) {
    //         cout << gauss[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 2 * R; i >= 0; i--) {
        int v = gauss[i][2 * R + 2];
        for (int j = i + 1; j <= 2 * R; j++) {
            subeq(v, mult(gauss[i][j + 1], sol[j]));
        }
        sol[i] = divide(v, gauss[i][i + 1]);
    }

    // for (int i = 0; i <= 2 * R; i++) cout << sol[i] << " ";
    // cout << endl;

    int ans = dp[DELTA][DELTA][0];
    for (int k = 0; k <= 2 * R; k++) {
        addeq(ans, mult(dp[DELTA][DELTA][k + 1], sol[k]));
    }
    
    cout << ans << endl;

    return 0;
} 