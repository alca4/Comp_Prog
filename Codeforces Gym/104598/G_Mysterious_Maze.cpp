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

ll add(const ll& a, const ll& b) {
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) {
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
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 160;
int N, X, Y;
map<int, int> xcoords;
map<int, int> ycoords;

int x1[MAXN];
int x2[MAXN];
int y11[MAXN];
int y2[MAXN];

int realx[MAXN * 4];
int realy[MAXN * 4];

vector<pii> nbs[MAXN * 4][MAXN * 4];
int dist[MAXN * 4][MAXN * 4];
int vis[MAXN * 4][MAXN * 4];

struct Info {
    int x, y, dist;
};

bool operator<(const Info& i1, const Info& i2) {
    return i1.dist > i2.dist;
}

void solve() {
    cin >> X >> Y >> N;
    for (int i = 1; i <= N; i++) {
        cin >> x1[i] >> y11[i] >> x2[i] >> y2[i];
        if (x1[i] > x2[i]) swap(x1[i], x2[i]);
        if (y11[i] > y2[i]) swap(y11[i], y2[i]);
        xcoords[x1[i]]++;
        xcoords[x2[i]]++;
        ycoords[y11[i]]++;
        ycoords[y2[i]]++;
    }
    xcoords[0]++;
    xcoords[X]++;
    ycoords[0]++;
    ycoords[Y]++;

    int xcnt = 0, ycnt = 0;
    for (auto n : xcoords) xcoords[n.FF] = ++xcnt;
    for (auto n : ycoords) ycoords[n.FF] = ++ycnt;

    for (int i = 1; i <= N; i++) {
        realx[xcoords[x1[i]]] = x1[i];
        realy[ycoords[y11[i]]] = y11[i];
        realx[xcoords[x2[i]]] = x2[i];
        realy[ycoords[y2[i]]] = y2[i];
        
        x1[i] = xcoords[x1[i]];
        y11[i] = ycoords[y11[i]];
        x2[i] = xcoords[x2[i]];
        y2[i] = ycoords[y2[i]];

        if (x1[i] == x2[i]) {
            // cout << i << endl;
            for (int j = y11[i]; j < y2[i]; j++) {
                // cout << x1[i] << " " << j << " " << j + 1 << endl;
                nbs[x1[i]][j].pb({x1[i], j + 1});
                nbs[x1[i]][j + 1].pb({x1[i], j});
            }
        } else {
            // cout << -i << endl;
            for (int j = x1[i]; j < x2[i]; j++) {
                nbs[j][y11[i]].pb({j + 1, y11[i]});
                nbs[j + 1][y11[i]].pb({j, y11[i]});
            }
        }
    }
    realx[1] = 0;
    realy[1] = 0;
    realx[xcoords[X]] = X;
    X = xcoords[X];
    realy[ycoords[Y]] = Y;
    Y = ycoords[Y];

    for (int i = 1; i <= xcnt; i++) for (int j = 1; j <= ycnt; j++) {
        dist[i][j] = INF;
    }
    dist[1][1] = 0;

    priority_queue<Info> pq;
    pq.push({1, 1, 0});
    while (!pq.empty()) {
        int x = pq.top().x;
        int y = pq.top().y;
        pq.pop();

        if (x == X && y == Y) continue;
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        for (pii nb : nbs[x][y]) {
            int x2 = nb.FF;
            int y2 = nb.SS;
            int w = abs(realx[x] - realx[x2]) + abs(realy[y] - realy[y2]);
            // cout << x << " " << y << " " << x2 << " " << y2 << " " << w << endl;

            if (dist[x2][y2] > dist[x][y] + w) {
                dist[x2][y2] = dist[x][y] + w;
                pq.push({x2, y2, dist[x2][y2]});
            }
        }
    }

    if (dist[X][Y] == INF) cout << -1 << endl;
    else cout << dist[X][Y] << endl;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    while (T--) solve();

    return 0;
} 