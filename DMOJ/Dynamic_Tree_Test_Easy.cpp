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
int N, Q;

#define lc ch[0]
#define rc ch[1]

int arr[MAXN];
vector<int> nbs[MAXN];

struct Node {
    ll v, sum, m, x, set, add;
    int p, pp, rev, ch[2], sz;
};
struct LCT {
    Node nodes[MAXN];
    int cap = 0;

    void DFS(int a, int p) {
        for (int nb : nbs[a]) if (nb != p) {
            DFS(nb, a);
            nodes[nb - 1].pp = a - 1;
        }
    }

    void build(int rt) {
        for (int i = 1; i <= N; i++) 
            insert(arr[i]);
        DFS(rt, -1);
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
 
    void insert(int v) {
        nodes[cap++] = {v, v, v, v, LINF, 0, -1, -1, 0, -1, -1, 1};
    }
 
    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }

        push(n);
        cout << n << " " << nodes[n].m << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
        pull(n);
    }

    void apply(int n, ll s, ll a, int r) {
        if (r) {
            nodes[n].rev ^= r;
            swap(nodes[n].lc, nodes[n].rc);
        }
        if (s != LINF) {
            nodes[n].set = s;
            nodes[n].add = 0;

            nodes[n].sum = s * nodes[n].sz;
            nodes[n].m = nodes[n].x = s;
            nodes[n].v = s;
        }
        if (a != 0) {
            nodes[n].add += a;

            nodes[n].sum += a * nodes[n].sz;
            nodes[n].m += a;
            nodes[n].x += a;
            nodes[n].v += a;
        }
    }

    void push(int n) {
        if (nodes[n].set == LINF && nodes[n].add == 0 && nodes[n].rev == 0) return;
        if (nodes[n].lc >= 0) apply(nodes[n].lc, nodes[n].set, nodes[n].add, nodes[n].rev);
        if (nodes[n].rc >= 0) apply(nodes[n].rc, nodes[n].set, nodes[n].add, nodes[n].rev);
        nodes[n].set = LINF;
        nodes[n].add = nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
        nodes[n].sum = nodes[n].v +
                       (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sum : 0) +
                       (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sum : 0);
        nodes[n].m = min({nodes[n].v, 
                         (nodes[n].lc >= 0 ? nodes[nodes[n].lc].m : LINF), 
                         (nodes[n].rc >= 0 ? nodes[nodes[n].rc].m : LINF)});
        nodes[n].x = max({nodes[n].v, 
                         (nodes[n].lc >= 0 ? nodes[nodes[n].lc].x : -LINF), 
                         (nodes[n].rc >= 0 ? nodes[nodes[n].rc].x : -LINF)});
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
        while (nodes[n].lc >= 0) n = nodes[n].lc;
        splay(n);
        return n;
    }

    void reroot(int n) { 
        access(n);
        apply(n, LINF, 0, 1);
    }

    void link(int m, int n) {
        reroot(m);
        nodes[m].pp = n;
    }

    void cut(int m, int n) {
        reroot(m);
        access(n);
        push(n);
        // cout << "edge destroyed between " << n << " and " << m << endl;
        nodes[n].lc = -1;
        nodes[m].p = -1;
        nodes[m].pp = -1;
        pull(n);
    }

    void update(int m, int n, int t, ll a) {
        reroot(m);
        access(n);

        if (t == 1) apply(n, a, 0, 0);
        if (t == 2) apply(n, LINF, a, 0);

        push(n);
    }

    ll query(int m, int n, int t) {
        reroot(m);
        access(n);

        push(n);
        ll ret;
        if (t == 3) ret = nodes[n].m;
        if (t == 4) ret = nodes[n].x;
        if (t == 5) ret = nodes[n].sum;
        return ret;
    }

    int lca(int m, int n) {
        access(m);
        int ret = access(n);
        return ret;
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

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    int rt;
    cin >> rt;
    lct.build(rt);
    rt--;

    // for (int i = 0; i < N; i++) 
    //         cout << i  << " " << lct.nodes[i].m << " " << lct.nodes[i].lc 
    //              << " " << lct.nodes[i].rc << " " << lct.nodes[i].pp << endl;

    // for (int i = 0; i < N; i++) 
    //     cerr << i << " " << lct.nodes[i].v << " " << lct.nodes[i].lc 
    //          << " " << lct.nodes[i].rc << " " << lct.nodes[i].pp << endl;

    for (int i = 0; i < Q; i++) {
        // cout << "Query " << i << endl;
        int t;
        cin >> t;
        if (t == 0) {
            int a;
            cin >> a;
            a--;
            rt = a;
        }
        if (t == 1) {
            int a, b, c;
            cin >> a >> b >> c;
            a--, b--;
            lct.update(a, b, 1, c);
        }
        if (t == 2) {
            int a, b, c;
            cin >> a >> b >> c;
            a--, b--;
            lct.update(a, b, 2, c);
        }
        if (t == 3) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << lct.query(a, b, 3) << endl;
        }
        if (t == 4) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << lct.query(a, b, 4) << endl;
        }
        if (t == 5) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << lct.query(a, b, 5) << endl;
        }
        if (t == 6) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            if (lct.lca(a, b) == a) continue;
            if (lct.nodes[a].p >= 0) lct.cut(lct.nodes[a].p, a);
            else lct.cut(lct.nodes[a].pp, a);
            lct.link(a, b);
        }
        if (t == 7) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << lct.lca(a, b) + 1 << endl;
        }

        // for (int i = 0; i < N; i++) 
        //     cout << i << " " << lct.nodes[i].v << " " << lct.nodes[i].lc 
        //          << " " << lct.nodes[i].rc << " " << lct.nodes[i].pp << endl;
        lct.reroot(rt);
    }

    return 0;
} 