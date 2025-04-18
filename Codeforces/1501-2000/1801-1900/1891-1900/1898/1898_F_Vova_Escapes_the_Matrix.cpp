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

const int MAXN = 1010;
int N, M;
int arr[MAXN][MAXN];
int x, y;
struct Point {
    int x, y, d, x0, y0;
};
vector<Point> vis[MAXN][MAXN];
int dfe[MAXN][MAXN];
int dfs[MAXN][MAXN];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void solve() {
    cin >> N >> M;
    int clear = 0;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
        char c;
        cin >> c;
        if (c == '#') arr[i][j] = 1;
        else if (c == 'V') x = i, y = j;
        else clear++;
    }

    int target = 0;
    queue<Point> bfs;
    vector<pii> exits;
    bfs.push({x, y, 0});
    while (!bfs.empty()) {
        Point p = bfs.front();
        bfs.pop();

        if (vis[p.x][p.y].size()) continue;
        vis[p.x][p.y].pb(p);
        dfs[p.x][p.y] = p.d;

        for (int i = 0; i < 4; i++) {
            if (p.x + dx[i] < 1 || p.x + dx[i] > N || p.y + dy[i] < 1 || p.y + dy[i] > M) {
                exits.pb({p.x, p.y});
            }
            else if (!arr[p.x + dx[i]][p.y + dy[i]]) 
                bfs.push({p.x + dx[i], p.y + dy[i], p.d + 1});
        }
    }
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) vis[i][j].clear();

    if (exits.size() > 2) target = 2;
    else target = exits.size();

    for (pii p : exits) {
        // cout << "can exit at " << p.FF  << " " << p.SS << endl;
        bfs.push({p.FF, p.SS, 0, p.FF, p.SS});
    }
    while (!bfs.empty()) {
        Point p = bfs.front();
        bfs.pop();

        // cout << "at " << p.x << " " << p.y << endl;
        // cout << "from " << p.d << " more distance" << endl;

        if (vis[p.x][p.y].size() == target) continue;
        if (vis[p.x][p.y].size() < target && 
            pii(p.x0, p.y0) == pii(vis[p.x][p.y][0].x0, vis[p.x][p.y][0].y0)) continue;
        vis[p.x][p.y].pb(p);
        dfe[p.x][p.y] += p.d;

        for (int i = 0; i < 4; i++) {
            if (p.x + dx[i] < 1 || p.x + dx[i] > N || p.y + dy[i] < 1 || p.y + dy[i] > M) {
                continue;
            }
            else if (!arr[p.x + dx[i]][p.y + dy[i]]) 
                bfs.push({p.x + dx[i], p.y + dy[i], p.d + 1, p.x0, p.y0});
        }
    }

    int ans = INF;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) 
        if (!arr[i][j] && vis[i][j].size() == target) {
        if (target == 2) {
            Point p1 = vis[i][j][0];
            Point p2 = vis[i][j][1];
            if (dfs[p1.x0][p1.y0] + dfs[p2.x0][p2.y0] == dfe[i][j])
                ans = min(ans, dfe[i][j]);
            else ans = min(ans, dfe[i][j] + dfs[i][j]);
        }
        else ans = min(ans, dfe[i][j] + dfs[i][j]);
    }
    cout << clear - ans << endl;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
        arr[i][j] = dfs[i][j] = dfe[i][j] = 0;
        vis[i][j].clear();
    }
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