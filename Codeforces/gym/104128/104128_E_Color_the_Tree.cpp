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

const int MAXN = 100010;
int N;
int D;
vector<int> nbs[MAXN];
ll arr[MAXN];

// lca
int depth[MAXN];
int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int T = 0;
void tour(int a, int p) {
    lift[a][0] = p;

    for (int j = 1; j < 32; j++)
        lift[a][j] = lift[lift[a][j - 1]][j - 1];

    in[a] = ++T;
    euler[T] = a;

    for (int i = 0; i < nbs[a].size(); i++)
        if (nbs[a][i] != p)
            tour(nbs[a][i], a);

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
void clear_lca() {
    for (int i = 1; i <= N; i++) {
        euler[in[i]] = euler[out[i]] = 0;
        in[i] = out[i] = 0;
        for (int j = 0; j < 32; j++)
            lift[i][j] = 0;
    }
    T = 0;
}

// hld
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
            return LINF;

        if (a <= ss && se <= b)
            return seg[cid];

        ll ans = LINF;
        int mid = (ss + se) / 2;

        if (a <= mid)
            mineq(ans, query(a, b, cid * 2, ss, mid));

        if (b > mid)
            mineq(ans, query(a, b, cid * 2 + 1, mid + 1, se));

        return ans;
    }
};

ST st;

// virtual tree
vector<int> key_nodes;
int key[MAXN];
vector<int> nbs2[MAXN];
stack<int> peoples;
vector<int> extras;

bool Comp(int a, int b) {
    return in[a] < in[b];
}

void setup_virtual_tree() {
    sort(key_nodes.begin(), key_nodes.end(), Comp);
    for (int n : key_nodes) key[n] = 1;

    peoples.push(key_nodes[0]);

    for (int j = 1; j < key_nodes.size(); j++) {
        int c = lca(peoples.top(), key_nodes[j]);

        if (c == peoples.top()) {
            peoples.push(key_nodes[j]);
            continue;
        }

        vector<int> tmp;

        while (peoples.size() && depth[c] < depth[peoples.top()]) {
            tmp.pb(peoples.top());
            peoples.pop();
        }

        tmp.pb(c);

        for (int j = 1; j < tmp.size(); j++) {
            nbs2[tmp[j]].pb(tmp[j - 1]);
        }

        if (!key[c]) {
            peoples.push(c);
            extras.pb(c);
            key[c] = 1;
        }

        peoples.push(key_nodes[j]);
    }

    while (peoples.size() > 1) {
        int x = peoples.top();
        peoples.pop();
        nbs2[peoples.top()].pb(x);
    }
}

void clear_virtual_tree() {
    for (int i : key_nodes) {
        nbs2[i].clear();
        key[i] = 0;
    }

    for (int i : extras) {
        nbs2[i].clear();
        key[i] = 0;
    }

    extras.clear();
    key_nodes.clear();
    while (!peoples.empty())
        peoples.pop();
}

void DFS(int a, int p) {
    lift[a][0] = p;
    D = max(depth[a], D);

    for (int nb : nbs[a]) 
        if (nb != p) {
            depth[nb] = depth[a] + 1;
            DFS(nb, a);
        }
}

ll DP(int a, int p, int d) {
    if (depth[a] == d)
        return st.query(1, d - depth[p], 1, 1, N);

    ll v1 = 0;
    ll v2 = st.query(d - depth[a] + 1, d - depth[p], 1, 1, N);
    // cout << d - depth[a] + 1 << " " << d - depth[p] << endl;

    for (int nb : nbs2[a]) 
        if (nb != p) 
            v1 += DP(nb, a, d);
    
    return min(v1, v2);
}

void solve() {
    // cout << "=====" << endl;
    cin >> N;

    st = ST(N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        st.update(i, arr[i], 1, 1, N);
    }
    
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }
    
    depth[1] = 1;
    DFS(1, 0);
    
    setup_lca();
    
    ll ans = 0;
    vector<int> nodes;
    nodes.pb(1);
    for (int i = 1; i <= D; i++) {
        key_nodes.pb(1);

        setup_virtual_tree();
        ll a = DP(1, 0, i);
        // cout << "ans do depth " << i << " is " << a << endl;
        ans += a;
        clear_virtual_tree();

        for (int j = 0; j < nodes.size(); j++) 
            for (int nb : nbs[nodes[j]])
                if (depth[nb] == i + 1)
                    key_nodes.pb(nb);
        nodes = key_nodes;
    }
    
    cout << ans << endl;

    st = ST();
    clear_lca();
    for (int i = 1; i <= N; i++) {
        arr[i] = depth[i] = 0;
        nbs[i].clear();
    }
    D = 0;
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
    while (T--) 
        solve();

    return 0;
} 