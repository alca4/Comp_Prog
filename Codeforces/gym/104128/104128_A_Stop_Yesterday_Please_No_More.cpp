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
ll MOD = 0;

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

const int MAXN = 1010;
int N, M, K;
string seq;
int vis[MAXN][MAXN];

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        while (a < arr.size()) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {return query(b) - query(a - 1);}

    void clear() {
        arr.resize(0);
    }
} bits[MAXN];

void solve() {
    cin >> N >> M >> K >> seq;
    for (int i = 1; i <= N; i++) bits[i] = BIT(M);

    int x = 1;
    int y = 1;
    int xend = N;
    int yend = M;
    int dx = 0;
    int dy = 0;
    for (int i = 0; i < seq.length(); i++) {
        char c = seq[i];
        if (c == 'U') dx--;
        if (c == 'D') dx++;
        if (c == 'L') dy--;
        if (c == 'R') dy++;

        x = max(x, 1 - min(0, dx));
        y = max(y, 1 - min(0, dy));
        xend = min(xend, N - max(0, dx));
        yend = min(yend, M - max(0, dy));
    }

    if (xend < x || yend < y) {
        // cout << "oob!" << endl;
        if (K == 0) cout << N * M << endl;
        else cout << 0 << endl;
    }
    else {
        for (int i = 0; i <= seq.length(); i++) {
            // cout << x << " " << y << " " << xend << " " << yend << endl;
            if (!vis[x][y]) {
                for (int j = x; j <= xend; j++) {
                    if (yend < M) bits[j].update(yend + 1, -1);
                    bits[j].update(y, 1);
                }

                vis[x][y] = 1;
            }

            if (i < seq.length()) {
                // cout << i << " " << seq.length() << endl;
                char c = seq[i];
                // cout << c << endl;
                if (c == 'U') {
                    x--;
                    xend--;
                }
                if (c == 'D') {
                    x++;
                    xend++;
                }
                if (c == 'L') {
                    y--;
                    yend--;
                }
                if (c == 'R') {
                    y++;
                    yend++;
                }
            }
        }

        int ans = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (bits[i].query(1, j) == (xend - x + 1) * (yend - y + 1) - K) ans++;
                // cout << bits[i].query(1, j) << " ";
            }
            // cout << endl;
        }
        
        cout << ans << endl;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) vis[i][j] = 0;
        bits[i].clear();
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 