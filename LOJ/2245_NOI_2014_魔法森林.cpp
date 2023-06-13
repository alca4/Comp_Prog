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

const int MAXN = 50010;
int N, M;
struct Edge {
    int a, b, c1, c2;
} edgelist[2 * MAXN];

bool operator<(const Edge& e1, const Edge& e2) {
    return e1.c1 < e2.c1;
}

#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sv;
    int svo;
    int p, pp, rev, ch[2], sz;
};
struct LCT {
    Node nodes[3 * MAXN];
    int cap = 0;
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }

    void con(int m, int n, int dir) {
        // cout << "edge prioritized between " << m << " and " << n << endl;
        push(m);
        nodes[m].ch[dir] = n;
        nodes[n].p = m;
        nodes[n].pp = -1;
        pull(m);
    }

    void dc(int n, int dir) {
        push(n);
        int n2 = nodes[n].ch[dir];
        if (n2 >= 0) {
            // cout << "edge normalized between " << n << " and " << n2 << endl;
            nodes[n2].p = -1;
            nodes[n2].pp = n;
            nodes[n].ch[dir] = -1;
        }
        pull(n);
    }
 
    void rotate(int n) {
        int p = nodes[n].p;
        int dn = dir(n);
        int dp = dir(p);
        push(p);
        push(n);
        int opp = nodes[n].ch[dn ^ 1];
        
        nodes[p].ch[dn] = opp;
        if (opp >= 0) nodes[opp].p = p;
 
        nodes[n].p = nodes[p].p;
        nodes[n].pp = nodes[p].pp;
        if (nodes[p].p >= 0) nodes[nodes[p].p].ch[dp] = n;
            
        nodes[n].ch[dn ^ 1] = p;
        nodes[p].p = n;
        nodes[p].pp = -1;
        pull(p);
        pull(n);
    }
 
    int splay(int n) {
        while (dir(n) >= 0) {
            int p = nodes[n].p;
            int dn = dir(n);
            int dp = dir(p);
 
            if (dp >= 0) rotate(dn == dp ? p : n);
            rotate(n);
        }
 
        return n;
    }
 
    void insert(ll v) {
        nodes[cap++] = {v, v, cap - 1, -1, -1, 0, -1, -1, 1};
    }

    void apply(int n, int r) {
        if (r) {
            nodes[n].rev ^= r;
            swap(nodes[n].lc, nodes[n].rc);
        }
    }

    void push(int n) {
        if (!nodes[n].rev) return;
        if (nodes[n].lc >= 0) apply(nodes[n].lc, nodes[n].rev);
        if (nodes[n].rc >= 0) apply(nodes[n].rc, nodes[n].rev);
        nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
        nodes[n].sv = max({nodes[n].v,
                          (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : -LINF), 
                          (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : -LINF)});
        
        if (nodes[n].sv == nodes[n].v) nodes[n].svo = n;
        if (nodes[n].sv == nodes[nodes[n].lc].sv) nodes[n].svo = nodes[nodes[n].lc].svo;
        if (nodes[n].sv == nodes[nodes[n].rc].sv) nodes[n].svo = nodes[nodes[n].rc].svo;
    }

    // lct methods
    int access(int n) {
        // cout << "accessing " << n << endl;
        int tn = n;
        splay(n);
        dc(n, 1);
        while (nodes[n].pp != -1) {
            int p = nodes[n].pp;
            // cout << "meeting " << p << endl;
            splay(p);
            if (nodes[p].rc >= 0) dc(p, 1);
            con(p, n, 1);
            n = p;
        }
        splay(tn);
        return n;
    }

    int root(int n) {
        access(n);
        while (nodes[n].lc >= 0) n = nodes[n].lc;
        splay(n);
        return n;
    }

    void reroot(int n) { 
        access(n);
        apply(n, 1);
    }

    void link(int m, int n) {
        if (root(m) == root(n)) return;
        reroot(m);
        // cout << "edge created from " << m << " to " << n << endl;
        nodes[m].pp = n;
    }

    void cut(int m, int n) {
        reroot(m);
        access(n);
        // cout << "edge destroyed between " << n << " and " << m << endl;
        push(n);
        nodes[n].lc = -1;
        nodes[m].p = -1;
        nodes[m].pp = -1;
        pull(n);
    }

    pll query(int m, int n) {
        reroot(m);
        access(n);

        push(n);
        return {nodes[n].sv, nodes[n].svo};
    }

    int lca(int m, int n) {
        access(m);
        return access(n);
    }
};

LCT lct;

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b, c1, c2;
        cin >> a >> b >> c1 >> c2;
        if (a > b) swap(a, b);
        edgelist[i] = {a, b, c1, c2};
    }

    for (int i = 0; i <= N; i++) lct.insert(-LINF);

    sort(edgelist + 1, edgelist + 1 + M);

    for (int i = 1; i <= M; i++) lct.insert(edgelist[i].c2);

    ll ans = LINF;
    for (int i = 1; i <= M; i++) {
        // cout << edgelist[i].a << " " << edgelist[i].b << endl;
        if (lct.root(edgelist[i].b) == lct.root(edgelist[i].a)) {
            pll v = lct.query(edgelist[i].a, edgelist[i].b);
            if (v.FF > edgelist[i].c2) {
                // cout << "replace" << endl;
                lct.cut(edgelist[v.SS - N].b, v.SS);
                lct.cut(v.SS, edgelist[v.SS - N].a);
                lct.link(edgelist[i].a, i + N);
                lct.link(i + N, edgelist[i].b);
            }
            // else cout << "ignore" << endl;
        }
        else {
            // cout << "create" << endl;
            lct.link(edgelist[i].a, i + N);
            lct.link(i + N, edgelist[i].b);
            // for (int i = 1; i <= N + M; i++)
            //     cout << lct.nodes[i].v << " " << lct.nodes[i].lc 
            //         << " " << lct.nodes[i].rc << " " << lct.nodes[i].pp << endl;
        }
        if (lct.root(1) == lct.root(N)) {
            // cout << "path exists of length " << lct.query(1, N) << endl;
            ans = min(ans, lct.query(1, N).FF + edgelist[i].c1);
        }
        
        // for (int i = 1; i <= N + M; i++)
        //     cout << lct.nodes[i].v << " " << lct.nodes[i].lc 
        //          << " " << lct.nodes[i].rc << " " << lct.nodes[i].pp << endl;
    }
    if (ans == LINF) cout << -1 << endl;
    else cout << ans << endl;

    return 0;
} 