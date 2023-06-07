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
ll MOD = 998244353;

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

const int MAXN = 1000010;
int N, Q;

#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sv, lm, la;
    bool rev;
    int p, ch[2], sz;
};
struct SplayTree {
    Node nodes[MAXN];
    int cap = 0;
    int rt;
 
    SplayTree() {rt = insert(0, 0, 0);}
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }
 
    void rotate(int n) {
        int p = nodes[n].p;
        push(p);
        push(n);
        int dn = dir(n);
        int dp = dir(p);
        int same = nodes[n].ch[dn];
        int opp = nodes[n].ch[dn ^ 1];
        
        int tsz = (same >= 0 ? nodes[same].sz : 0);
        nodes[p].ch[dn] = opp;
        if (opp >= 0) nodes[opp].p = p;
 
        nodes[n].p = nodes[p].p;
        if (nodes[p].p >= 0) nodes[nodes[p].p].ch[dp] = n;
            
        nodes[n].ch[dn ^ 1] = p;
        nodes[p].p = n;
 
        nodes[n].sz = nodes[p].sz;
        nodes[p].sz -= tsz + 1;
 
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
 
        return rt = n;
    }
 
    int find(int n, int v, int before) {
        push(n);
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        int ret;
        if (nodes[n].lc >= 0 && v < d) ret = find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) ret = find(nodes[n].rc, v, d + 1);
        else ret = splay(n);
        pull(n);
        return ret;
    }
 
    pii split(int n, int v) {
        if (n < 0) return pii(-1, -1);
        n = find(n, v, 0);
        int n2 = nodes[n].rc;
        if (n2 == -1) return pii(n, -1);
        
        push(n);
        nodes[n2].p = -1;
        nodes[n].rc = -1;
 
        nodes[n].sz -= nodes[n2].sz;
        pull(n);
        return pii(n, n2);
    }
 
    int merge(int m, int n) {
        if (m == -1) return n;
        if (n == -1) return m;
 
        n = find(n, 0, 0);

        push(n);
        nodes[n].lc = m;
        nodes[m].p = n;
        nodes[n].sz += nodes[m].sz;
        pull(n);
        return n;
    }
 
    int insert(int n, int idx, int v) {
        nodes[cap++] = {v, v, 1, 0, 0, -1, -1, -1, 1};
        if (cap == 1) return rt = 0;

        pii x = split(n, idx - 1);

        rt = merge(x.FF, cap - 1);
        rt = merge(rt, x.SS);

        return rt;
    }

    int erase(int n, int idx) {
        pii x = split(n, idx - 1);
        pii y = split(x.SS, 0);
        rt = merge(x.FF, y.SS);
        return rt;
    }
 
    // updates and queries
    void apply(int n, int b, int c, bool r) {
        nodes[n].la = (nodes[n].la * b + c) % MOD;
        nodes[n].lm = (nodes[n].lm * b) % MOD;
        nodes[n].v = (nodes[n].v * b + c) % MOD;
        nodes[n].sv = (nodes[n].sv * b + 1ll * c * nodes[n].sz) % MOD;
        nodes[n].rev ^= r;
        if (r) swap(nodes[n].lc, nodes[n].rc);
    }

    void push(int n) {
        if (nodes[n].lm == 1 && nodes[n].la == 0 && nodes[n].rev == 0) return;
        
        if (nodes[n].lc >= 0) 
            apply(nodes[n].lc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        if (nodes[n].rc >= 0) 
            apply(nodes[n].rc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        nodes[n].la = nodes[n].rev = 0;
        nodes[n].lm = 1;
    }

    void pull(int n) {
        nodes[n].sv = (nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0)) % MOD;
    }

    void update(int n, int l, int r, int a, int b) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        apply(y.FF, a, b, 0);
        push(y.FF);

        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
    }

    void reverse(int n, int l, int r) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        apply(y.FF, 1, 0, 1);
        push(y.FF);

        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
    }
 
    ll query(int n, int l, int r) {
        pii x = split(n, l - 1);
        pii y = split(x.SS, r - l);

        push(y.FF);
        ll v = nodes[y.FF].sv;
 
        x.FF = merge(x.FF, y.FF);
        rt = merge(x.FF, y.SS);
        return v;
    }
 
    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }
        // push(n);
        cout << n << " " << nodes[n].sv << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);

        // pull(n);
    }
};

SplayTree st;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        st.insert(st.rt, i, n);
    }

    for (int i = 1; i <= Q; i++) {
        // cout << "===== " << i << endl;
        int t;
        cin >> t;
        // cout << t << endl;
        if (t == 0) {
            int a, b;
            cin >> a >> b;
            a++;
            st.insert(st.rt, a, b);
        }
        if (t == 1) {
            int a;
            cin >> a;
            a++;
            st.erase(st.rt, a);
        }
        if (t == 2) {
            int l, r;
            cin >> l >> r;
            l++;
            st.reverse(st.rt, l, r);
        }
        if (t == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            l++;
            st.update(st.rt, l, r, b, c);
        }
        if (t == 4) {
            int l, r;
            cin >> l >> r;
            l++;
            cout << st.query(st.rt, l, r) << endl;
        }
    }

    return 0;
} 