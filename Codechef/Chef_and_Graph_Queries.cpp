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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
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

const int MAXN = 200010;
const int S = 450;
int N, M, Q;
pii edgelist[MAXN];
struct Query {
    int x, y, id;
} queries[MAXN];
int ans[MAXN];

bool operator<(const Query& q1, const Query& q2) {
    return pii(q1.x, q1.y) < pii(q2.x, q2.y);
}

int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
void clear_dsu() {for (int i = 1; i <= N; i++) p[i] = sz[i] = 0;}
int root(int a) {return (a == p[a] ? a : root(p[a]));}
stack<pii> ops;
int combine(int a, int b) {
    a = root(a), b = root(b);
    if (a == b) return 0;

    ops.push(pii(a, b));
    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}
void undo() {
    int a = ops.top().FF, b = ops.top().SS;
    ops.pop();
    if (sz[a] < sz[b]) swap(a, b);
    sz[a] -= sz[b];
    p[b] = b;
}

void solve() {
    cin >> N >> M >> Q;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        edgelist[i] = pii(a, b);
    }

    for (int i = 1; i <= Q; i++) {
        int a, b;
        cin >> a >> b;
        queries[i] = {a, b, i};
    }

    sort(queries + 1, queries + Q + 1);

    setup_dsu();
    int j = 1;
    for (int i = 1; i <= S; i++) {
        int k = j;
        while (k <= Q && queries[k].x <= i * S) k++;
        for (int h = j; h < k; h++) swap(queries[h].x, queries[h].y);
        sort(queries + j, queries + k);
        for (int h = j; h < k; h++) swap(queries[h].x, queries[h].y);

        int l = i * S + 1, r = i * S;
        for (int h = j; h < k; h++) {
            if (queries[h].y <= i * S) {
                int v = 0;
                for (int n = queries[h].x; n <= queries[h].y; n++) 
                    v += combine(edgelist[n].FF, edgelist[n].SS);
                ans[queries[h].id] = N - ops.size();
                while (ops.size()) undo();
            }
            else {
                int v = 0;
                while (r < queries[h].y) {
                    r++;
                    combine(edgelist[r].FF, edgelist[r].SS);
                }
                while (l > queries[h].x) {
                    l--;
                    v += combine(edgelist[l].FF, edgelist[l].SS);
                }
                ans[queries[h].id] = N - ops.size();
                while (v--) undo();
                l = i * S + 1;
            }
        }
        while (ops.size()) undo();
        j = k;
    }

    for (int i = 1; i <= M; i++) edgelist[i] = pii(0, 0);
    for (int i = 1; i <= Q; i++) {
        queries[i] = {0, 0, 0};
        cout << ans[i] << endl;
        ans[i] = 0;
    }
    clear_dsu();
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 