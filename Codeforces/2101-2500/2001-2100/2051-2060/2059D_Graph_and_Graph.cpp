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

const int MAXN = 1010;
int N, S[2], M[2];
vector<int> nbs[2][MAXN];
int dist[MAXN][MAXN];
int vis[MAXN][MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[0][i].clear();
        nbs[1][i].clear();
        for (int j = 1; j <= N; j++) dist[i][j] = vis[i][j] = 0;
    }
}

void solve() {
    cin >> N >> S[0] >> S[1];
    for (int j = 0; j < 2; j++) {
        cin >> M[j];
        for (int i = 1; i <= M[j]; i++) {
            int a, b;
            cin >> a >> b;
            nbs[j][a].pb(b);
            nbs[j][b].pb(a);
        }
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) dist[i][j] = INF;
    dist[S[0]][S[1]] = 0;

    priority_queue<pair<int, pii>> pq;
    pq.push(make_pair(0, pii(S[0], S[1])));
    while (!pq.empty()) {
        int d = -pq.top().FF;
        int n1 = pq.top().SS.FF;
        int n2 = pq.top().SS.SS;
        pq.pop();

        if (vis[n1][n2]) continue;
        // cout << n1 << " " << n2 << endl;
        vis[n1][n2] = 1;

        for (int nb1 : nbs[0][n1]) for (int nb2 : nbs[1][n2]) {
            // cout << "try for " << nb1 << " " << nb2 << endl;
            mineq(dist[nb1][nb2], d + abs(nb1 - nb2));
            pq.push(make_pair(-dist[nb1][nb2], pii(nb1, nb2)));
        }
    }

    int ans = INF;
    for (int i = 1; i <= N; i++) {
        sort(nbs[0][i].begin(), nbs[0][i].end());
        sort(nbs[1][i].begin(), nbs[1][i].end());

        int p1 = 0, p2 = 0;
        while (p1 < size(nbs[0][i]) && p2 < size(nbs[1][i])) {
            if (nbs[0][i][p1] == nbs[1][i][p2]) {
                mineq(ans, dist[nbs[0][i][p1]][nbs[0][i][p1]]);
                p1++;
                p2++;
            }
            else if (nbs[0][i][p1] < nbs[1][i][p2]) p1++;
            else p2++;
        }
    }

    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;

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