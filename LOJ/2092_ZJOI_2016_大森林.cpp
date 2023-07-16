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

const int MAXN = 100010;
int N, M, U, Q;
int Z, O, T;

#define lc ch[0]
#define rc ch[1]

struct Node {
    int v, sv, p, pp, rev, ch[2], sz;
};
struct LCT {
    Node nodes[2 * MAXN];
    int cap = 0;

    void insert(int a, int v) {
        nodes[a] = {v, v, -1, -1, 0, -1, -1, 1};
    }
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }

    void con(int m, int n, int dir) {
        push(m);
        // cout << "edge created between " << m << " and " << n << endl;
        nodes[m].ch[dir] = n;
        nodes[n].p = m;
        nodes[n].pp = -1;
        pull(m);
    }

    void dc(int n, int dir) {
        push(n);
        int n2 = nodes[n].ch[dir];
        if (n2 >= 0) {
            // cout << "edge destroyed between " << n << " and " << n2 << endl;
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
 
    void print() {
        for (int i = 1; i <= M + 2; i++) {
            cout << i << " " << nodes[i].v << " " << nodes[i].lc << " " 
                 << nodes[i].rc << " " << nodes[i].pp << endl;
        }
    }

    void apply(int n,int r) {
        if (r) {
            nodes[n].rev ^= r;
            swap(nodes[n].lc, nodes[n].rc);
        }
    }

    void push(int n) {
        if (nodes[n].rev == 0) return;
        if (nodes[n].lc >= 0) apply(nodes[n].lc, nodes[n].rev);
        if (nodes[n].rc >= 0) apply(nodes[n].rc, nodes[n].rev);
        nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
        nodes[n].sv = nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0);
    }

    // lct methods
    int access(int n) {
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
        // cerr << "trying to rut" << endl;
        while (nodes[n].lc >= 0) n = nodes[n].lc;
        splay(n);
        // cerr << "rutted" << endl;
        return n;
    }

    void reroot(int n) { 
        access(n);
        apply(n, 1);
    }

    void link(int m, int n) {
        assert(root(m) != root(n));
        // cout << "linking " << m << " " << n << endl;
        reroot(m);
        nodes[m].pp = n;
        reroot(1);
    }

    void cut(int m, int n) {
        assert(root(m) == root(n));
        // cout << "cutting " << m << " " << n << endl;
        reroot(m);
        access(n);
        push(n);
        // cout << "edge destroyed between " << n << " and " << m << endl;
        nodes[n].lc = -1;
        nodes[m].p = -1;
        nodes[m].pp = -1;
        pull(n);
        reroot(1);
    }

    ll query(int m, int n) {
        reroot(m);
        access(n);

        push(n);
        int v = nodes[n].sv;
        reroot(1);
        return v;
    }

    int lca(int m, int n) {
        access(m);
        return access(n);
    }
};

struct Event {
    int type, t, id, m, n;
};
bool operator<(const Event& e1, const Event& e2) {
    return pii(abs(e1.id), e1.t) < pii(abs(e2.id), e2.t);
}
Event updates[4 * MAXN];
struct Query {
    int m, n, id;
};
vector<Query> queries[MAXN];
vector<int> zeros, ones;
int above[2 * MAXN], under[2 * MAXN];
vector<pii> ans;

int L[2 * MAXN], R[2 * MAXN];

LCT lct;

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    L[1] = 1, R[1] = N;
    lct.insert(1, 1);
    lct.insert(2, 0);
    lct.link(2, 1);
    zeros.pb(0);
    zeros.pb(1);
    Z = 1;
    ones.pb(2);
    O = 0;
    for (int i = 3; i <= M + 2; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            Z++;
            cin >> L[Z] >> R[Z];
            updates[++U] = {0, i, L[Z], Z, O};
            updates[++U] = {0, i, -(R[Z] + 1), Z, O};
            zeros.pb(i);
            lct.insert(i, 1);
        }
        if (t == 1) {
            int l, r, n;
            cin >> l >> r >> n;
            l = max(l, L[n]);
            r = min(r, R[n]);
            if (l > r) continue;
            O++;
            updates[++U] = {1, i, l, O, n};
            updates[++U] = {1, i, -(r + 1), O, n};
            lct.insert(i, 0);
            lct.link(i, ones.back());
            ones.pb(i);
        }
        if (t == 2) {
            T++;
            int x, m, n;
            cin >> x >> m >> n;
            queries[x].pb({m, n, i});
        }
    }

    // lct.print();

    // cout << "updating time baybee" << endl;
    sort(updates + 1, updates + 1 + U);
    // for (int i = 1; i <= U; i++) 
    //     cout << updates[i].t << " " << updates[i].m << " " << updates[i].n << endl;

    int j = 1;
    for (int i = 1; i <= N; i++) {
        while (updates[j].id == 0) j++;
        while (j <= U && abs(updates[j].id) == i) {
            // cout << updates[j].id << " " << updates[j].type << endl;
            if (updates[j].id > 0) {
                if (updates[j].type == 0) {
                    // cout << "growing node " << zeros[updates[j].m] << " " << ones[updates[j].n] << endl;
                    lct.link(zeros[updates[j].m], ones[updates[j].n]);
                }

                if (updates[j].type == 1) {
                    // cout << "switching growth " << zeros[updates[j].n] << " " << ones[updates[j].m] << endl;
                    // cout << ones[updates[j].m - 1] << " " << ones[updates[j].m] << endl;
                    lct.cut(ones[updates[j].m - 1], ones[updates[j].m]);
                    lct.link(ones[updates[j].m], zeros[updates[j].n]);
                }
            } 
            else {
                if (updates[j].type == 0) {
                    // cout << "ungrowing node " << endl;
                    lct.cut(ones[updates[j].n], zeros[updates[j].m]);
                }

                if (updates[j].type == 1) {
                    // cout << "unswitching growth " << endl;
                    lct.cut(zeros[updates[j].n], ones[updates[j].m]);
                    lct.link(ones[updates[j].m], ones[updates[j].m - 1]);
                }
            }

            j++;
        }

        // cout << "tree " << i << endl;
        for (Query q : queries[i]) {
            // cout << "querying " << zeros[q.m] << " " << zeros[q.n] << endl;
            int v = lct.query(zeros[q.m], zeros[q.n]);
            if (lct.nodes[lct.lca(zeros[q.m], zeros[q.n])].v == 0) v++;
            ans.pb({q.id, v});
        }
        // lct.print();

    }

    sort(ans.begin(), ans.end());
    for (pii n : ans) cout << n.SS - 1 << endl;

    return 0;
} 