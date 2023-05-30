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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll &a, const ll &b) {
    ll x = a + b;

    if (a + b >= MOD)
        x -= MOD;

    return x;
}
ll sub(const ll &a, const ll &b) {
    ll x = a - b;

    if (a - b < 0)
        x += MOD;

    return x;
}
ll mult(const ll &a, const ll &b) {
    return (a * b) % MOD;
}
ll binexp[32];
ll power(ll a, ll b) {
    ll n = b;
    ll ans = 1;

    binexp[0] = a;

    for (int i = 1; i < 32; i++)
        binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0) {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll &a, const ll &b) {
    return (a * power(b, MOD - 2)) % MOD;
}
template<class X, class Y> void maxeq(X &x, Y y) {
    if (x < y)
        x = y;
}
template<class X, class Y> void mineq(X &x, Y y) {
    if (x > y)
        x = y;
}
template<class X, class Y> void addeq(X &x, Y y) {
    x = add(x, y);
}
template<class X, class Y> void subeq(X &x, Y y) {
    x = sub(x, y);
}
template<class X, class Y> void multeq(X &x, Y y) {
    x = mult(x, y);
}
template<class X, class Y> void diveq(X &x, Y y) {
    x = divide(x, y);
}

const int MAXN = 250010;
int N, Q;

struct ST {
    vector<ll> seg;

    ST() {
        ST(0);
    }

    ST(int n) {
        seg.resize(1 + 4 * n);
    }

    void update(int a, int v, int cid, int ss, int se) {
        if (ss == se) {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;

        if (a <= mid)
            update(a, v, cid * 2, ss, mid);
        else
            update(a, v, cid * 2 + 1, mid + 1, se);

        seg[cid] = min(seg[cid * 2], seg[cid * 2 + 1]);
    }

    ll query(int a, int b, int cid, int ss, int se) {
        if (a > b)
            return INF;

        if (a <= ss && se <= b)
            return seg[cid];

        ll ans = INF;
        int mid = (ss + se) / 2;

        if (a <= mid)
            mineq(ans, query(a, b, cid * 2, ss, mid));

        if (b > mid)
            mineq(ans, query(a, b, cid * 2 + 1, mid + 1, se));

        return ans;
    }
};

int w[MAXN];
int sz[MAXN];
vector<pii> nbs[MAXN];
int hchild[MAXN];
pii loc[MAXN];
ST chains[MAXN];
vector<int> nodes[MAXN];
int chainsz[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int depth[MAXN];
int T = 0;
void tour(int a, int p) {
    lift[a][0] = p;

    for (int j = 1; j < 32; j++)
        lift[a][j] = lift[lift[a][j - 1]][j - 1];

    in[a] = ++T;
    euler[T] = a;

    for (int i = 0; i < nbs[a].size(); i++)
        if (nbs[a][i].FF != p)
            tour(nbs[a][i].FF, a);

    out[a] = ++T;
    euler[T] = -a;
}
bool is_anc(int a, int b) {
    return in[a] <= in[b] && out[b] <= out[a];
}
void setup_lca() {
    tour(1, 0);
}
int lca(int a, int b) {
    if (is_anc(a, b))
        return a;

    if (is_anc(b, a))
        return b;

    for (int i = 31; i >= 0; i--)
        if (lift[a][i] != 0 && !is_anc(lift[a][i], b))
            a = lift[a][i];

    return lift[a][0];
}

bool Comp(pii a, pii b) {
    return sz[a.FF] < sz[b.FF];
}

int C = 0;
void HLD_DFS(int a, int p) {
    sz[a] = 1;
    vector<pii> check;

    for (pii nb : nbs[a])
        if (nb.FF != p) {
            depth[nb.FF] = depth[a] + 1;
            HLD_DFS(nb.FF, a);
            w[nb.FF] = nb.SS;
            sz[a] += sz[nb.FF];
            lift[nb.FF][0] = a;
            check.pb(nb);
        }

    sort(check.rbegin(), check.rend(), Comp);

    if (check.size()) {
        hchild[a] = check[0].FF;
        loc[a] = pii(loc[hchild[a]].FF, loc[hchild[a]].SS + 1);
    } else {
        loc[a] = pii(++C, 1);
        nodes[C].pb(0);
    }

    nodes[loc[a].FF].pb(a);
    chainsz[loc[a].FF]++;
}

void setup_hld() {
    HLD_DFS(1, 0);
    setup_lca();

    w[1] = INF;

    for (int i = 1; i <= C; i++) {
        chains[i] = ST(chainsz[i]);

        for (int j = 1; j <= chainsz[i]; j++)
            chains[i].update(j, w[nodes[i][j]], 1, 1, chainsz[i]);
    }
}

ll hld_query(int a, int b) {
    int c = lca(a, b);

    int aloc = loc[a].FF;
    int bloc = loc[b].FF;
    ll ans = INF;

    while (a && loc[a].FF != loc[c].FF) {
        mineq(ans, chains[aloc].query(loc[a].SS, chainsz[aloc], 1, 1, chainsz[aloc]));
        a = lift[nodes[aloc][chainsz[aloc]]][0];
        aloc = loc[a].FF;
    }

    if (a)
        mineq(ans, chains[aloc].query(loc[a].SS, loc[c].SS - 1, 1, 1, chainsz[aloc]));

    while (b && loc[b].FF != loc[c].FF) {
        mineq(ans, chains[bloc].query(loc[b].SS, chainsz[bloc], 1, 1, chainsz[bloc]));
        b = lift[nodes[bloc][chainsz[bloc]]][0];
        bloc = loc[b].FF;
    }

    if (b)
        mineq(ans, chains[bloc].query(loc[b].SS, loc[c].SS - 1, 1, 1, chainsz[bloc]));

    return ans;
}

set<int> good;
vector<int> queries;
set<int> players;
int ans[2 * MAXN];
vector<pii> nbs2[2 * MAXN];
stack<int> peoples;
int key[MAXN];

void setup_virtual_tree() {
    for (int n : queries) players.insert(n);

    for (int j = 1; j < queries.size(); j++) {
        int c = lca(peoples.top(), queries[j]);

        if (c == peoples.top()) {
            peoples.push(queries[j]);
            continue;
        }

        vector<int> tmp;

        while (peoples.size() && depth[c] < depth[peoples.top()]) {
            tmp.pb(peoples.top());
            peoples.pop();
        }

        tmp.pb(c);

        for (int j = 1; j < tmp.size(); j++) 
            nbs2[tmp[j]].pb(pii(tmp[j - 1], hld_query(tmp[j], tmp[j - 1])));

        if (!players.count(c)) {
            peoples.push(c);
            players.insert(c);
        }

        peoples.push(queries[j]);
    }

    while (peoples.size() > 1) {
        int x = peoples.top();
        peoples.pop();
        nbs2[peoples.top()].pb(pii(x, hld_query(x, peoples.top())));
    }

    for (int n : players) {
        nbs2[n].clear();
        dp[n] = 0;
        key[n] = 0;
    }

    queries.clear();
    players.clear();
}

ll dp[MAXN];
ll DP(int a, int p) {
    for (pll nb : nbs2[a])
        if (nb.FF != p) {
            DP(nb.FF, a);

            if (key[nb.FF])
                dp[a] += nb.SS;
            else
                dp[a] += min(nb.SS, dp[nb.FF]);
        }
    
    // cout << "dp at " << a << " is " << dp[a] << endl;

    return dp[a];
}

bool Comp2(int a, int b) {
    return in[a] < in[b];
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    for (int i = 1; i < N; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        nbs[a].pb(pii(b, c));
        nbs[b].pb(pii(a, c));
    }

    setup_hld();

    cin >> Q;

    peoples.push(1);

    for (int i = 1; i <= Q; i++) {

        // cout << "Query " << i << endl;

        int k;
        cin >> k;

        queries.pb(1);

        for (int j = 1; j <= k; j++) {
            int n;
            cin >> n;
            queries.pb(n);
        }

        sort(queries.begin(), queries.end(), Comp2);

        for (int j = 0; j < queries.size(); j++) {
            // cout << queries[j] << " " << in[queries[j]] << endl;
            key[queries[j]] = 1;
        }

        setup_virtual_tree();

        cout << DP(1, 0) << endl;
    }

    return 0;
}