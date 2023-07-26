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

const int MAXN = 200010;
int N, Q;

struct Node {
    ll lans, rans, ans, sum;

    Node() {
        lans = rans = ans = sum = -LINF;
    }

    Node(ll a, ll b, ll c, ll d) {
        lans = a;
        rans = b;
        ans = c;
        sum = d;
    }
};

Node combine(const Node& n1, const Node& n2) {
    if (n1.lans == n1.rans && n1.rans == n1.ans && n1.ans == n1.sum && n1.sum == -LINF) 
        return n2;
    if (n2.lans == n2.rans && n2.rans == n2.ans && n2.ans == n2.sum && n2.sum == -LINF) 
        return n1;
    return Node(max(n1.lans, n1.sum + n2.lans),
                max(n1.rans + n2.sum, n2.rans),
                max({n1.ans, n1.rans + n2.lans, n2.ans}),
                n1.sum + n2.sum);
}

struct ST
{
    vector<Node> seg;

    ST() {ST(0);}

    ST(int n) {seg.resize(1 + 4 * n);}

    void update(int a, ll v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = {v, v, v, v};
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = combine(seg[cid * 2], seg[cid * 2 + 1]);
    }

    Node query(int a, int b, int cid, int ss, int se)
    {
        if (a > b) return Node();
        if (a <= ss && se <= b) return seg[cid];

        Node ans;
        int mid = (ss + se) / 2;
        if (a <= mid) {
            ans = combine(ans, query(a, b, cid * 2, ss, mid));
        }
        if (b > mid) {
            ans = combine(ans, query(a, b, cid * 2 + 1, mid + 1, se));
        }
        return ans;
    }

    void clear(int cid, int ss, int se) {
        seg[cid] = Node();
        if (ss == se) return;

        int mid = (ss + se) / 2;
        if (ss <= mid) clear(cid * 2, ss, mid);
        else clear(cid * 2 + 1, mid + 1, se);
    }
};

int w[MAXN];
int sz[MAXN];
vector<int> nbs[MAXN];
int hchild[MAXN];
pii loc[MAXN];
ST chains[MAXN];
vector<int> nodes[MAXN];
int chainsz[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int T = 0;
void tour(int a, int p)
{
    lift[a][0] = p;
    for (int j = 1; j < 32; j++) 
        lift[a][j] = lift[lift[a][j - 1]][j - 1];
    in[a] = ++T;
    euler[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
    out[a] = ++T;
    euler[T] = -a;
}
bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
void setup_lca() {tour(1, 0);}
int lca(int a, int b)
{
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = 31; i >= 0; i--)
        if (lift[a][i] != 0 && !is_anc(lift[a][i], b)) a = lift[a][i];
    
    return lift[a][0];
}
void clear_lca() {
    for (int i = 1; i <= N; i++) {
        in[i] = out[i] = euler[i * 2 - 1] = euler[i * 2] = 0;
        for (int j = 0; j < 32; j++) lift[i][j] = 0;
        T = 0;
    }
}

bool Comp(int a, int b) {return sz[a] < sz[b];}

int C = 0;
void DFS(int a, int p)
{
    sz[a] = 1;
    vector<int> check;
    for (int nb : nbs[a]) if (nb != p)
    {
        DFS(nb, a);
        sz[a] += sz[nb];
        lift[nb][0] = a;
        check.pb(nb);
    }
    
    sort(check.rbegin(), check.rend(), Comp);
    if (check.size())
    {
        hchild[a] = check[0];
        loc[a] = pii(loc[hchild[a]].FF, loc[hchild[a]].SS + 1);
    }
    else 
    {
        loc[a] = pii(++C, 1);
        nodes[C].pb(0);
    }
    nodes[loc[a].FF].pb(a);
    chainsz[loc[a].FF]++;
}

void setup_hld()
{
    DFS(1, 0);
    setup_lca();
    for (int i = 1; i <= C; i++) 
    {
        chains[i] = ST(chainsz[i]);
        for (int j = 1; j <= chainsz[i]; j++)
            chains[i].update(j, w[nodes[i][j]], 1, 1, chainsz[i]);
    }
}

ll answer(int a, int b)
{
    int c = lca(a, b);

    int aloc = loc[a].FF;
    int bloc = loc[b].FF;
    Node ans;
    while (a && loc[a].FF != loc[c].FF)
    {
        ans = combine(ans, chains[aloc].query(loc[a].SS, chainsz[aloc], 1, 1, chainsz[aloc]));
        a = lift[nodes[aloc][chainsz[aloc]]][0];
        aloc = loc[a].FF;
    }
    if (a) {
        ans = combine(ans, chains[aloc].query(loc[a].SS, loc[c].SS, 1, 1, chainsz[aloc]));
    }

    Node ans2;
    while (b && loc[b].FF != loc[c].FF)
    {
        ans2 = combine(ans2, chains[bloc].query(loc[b].SS, chainsz[bloc], 1, 1, chainsz[bloc]));
        b = lift[nodes[bloc][chainsz[bloc]]][0];
        bloc = loc[b].FF;
    }
    if (b) {
        ans2 = combine(ans2, chains[bloc].query(loc[b].SS, loc[c].SS - 1, 1, 1, chainsz[bloc]));
    }

    swap(ans2.lans, ans2.rans);

    return combine(ans, ans2).ans;
}

void clear_hld() {
    clear_lca();
    for (int i = 1; i <= N; i++) {
        w[i] = sz[i] = hchild[i] = 0;
        loc[i] = {0, 0};
    }
    for (int i = 1; i <= C; i++) {
        chains[i].seg.clear();
        nodes[i].clear();
        chainsz[i] = 0;
    }
    C = 0;
}

struct Query {
    int t;
    int a, b, c;
} queries[MAXN];

int sols[MAXN], nz[MAXN];

void solve() {
    cin >> Q;
    int N = 0;
    w[++N] = 1;
    for (int i = 1; i <= Q; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            int u, d;
            cin >> u >> d;
            queries[i] = {0, u, d};
            w[++N] = d;
            nbs[u].pb(N);
        }
        if (c == '?') {
            int u, d, t;
            cin >> u >> d >> t;
            queries[i] = {1, u, d, t};
        }
    }

    setup_hld();

    for (int i = 1; i <= Q; i++) if (queries[i].t == 1 && queries[i].c >= 0) {
        // cout << queries[i].a << " " << queries[i].b << " " << answer(queries[i].a, queries[i].b) << endl;
        if (lca(queries[i].a, queries[i].b) == queries[i].a) swap(queries[i].a, queries[i].b);
        sols[i] = (answer(queries[i].a, queries[i].b) >= queries[i].c);
    }

    clear_hld();

    for (int i = 1; i <= N; i++) w[i] *= -1;

    setup_hld();

    for (int i = 1; i <= Q; i++) if (queries[i].t == 1 && queries[i].c < 0) {
        // cout << queries[i].a << " " << queries[i].b << " " << answer(queries[i].a, queries[i].b) << endl;
        if (lca(queries[i].a, queries[i].b) == queries[i].a) swap(queries[i].a, queries[i].b);
        sols[i] = (answer(queries[i].a, queries[i].b) >= abs(queries[i].c));
    }
    
    clear_hld();

    for (int i = 1; i <= Q; i++) if (queries[i].t == 1) {
        if (sols[i]) cout << "YES" << endl;
        else cout << "NO" << endl;
    }

    for (int i = 1; i <= N; i++) {
        w[i] = 0;
        nbs[i].clear();
    }

    for (int i = 1; i <= Q; i++) {
        queries[i] = {0, 0, 0, 0};
        sols[i] = 0;
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