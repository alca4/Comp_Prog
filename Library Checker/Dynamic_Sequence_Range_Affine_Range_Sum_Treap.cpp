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

int rand32() {
    return (rand() << 16) | (rand());
}

struct Node {
    ll v, v2, sv, la, lm;
    bool rev;
    int p, ch[2], sz;
};
struct Treap {
    Node nodes[MAXN];
    int cap = 0;
    int rt;

    Treap() {insert(0, 0, 0);}

    int find(int n, int v, int before) {
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        if (nodes[n].lc >= 0 && v < d) return find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) return find(nodes[n].rc, v, d + 1);
        else return n;
    }

    pii split(int n, int v, int before) {
        if (n >= 0) {
            push(n);
            int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
            if (v < d) {
                pii x = split(nodes[n].lc, v, before);
                nodes[n].lc = x.SS;
                pull(n);
                return pii(x.FF, n);
            }
            else {
                pii x = split(nodes[n].rc, v, d + 1);
                nodes[n].rc = x.FF;
                pull(n);
                return pii(n, x.SS);
            }
        }
        return pii(-1, -1);
    }

    int merge(int m, int n) {
        if (m == -1) return n;
        if (n == -1) return m;

        if (nodes[m].v2 > nodes[n].v2) {
            push(m);
            nodes[m].rc = merge(nodes[m].rc, n);
            pull(m);
            return m;
        }
        else {
            push(n);
            nodes[n].lc = merge(m, nodes[n].lc);
            pull(n);
            return n;
        }
    }

    void insert(int n, int idx, int v) {
        nodes[cap++] = {v, rand32(), v, 0, 1, 0, -1, -1, -1, 1};
        if (cap == 1) {
            rt = 0;
            return;
        }

        pii x = split(n, idx - 1, 0);
        rt = merge(merge(x.FF, cap - 1), x.SS);
    }

    void erase(int n, int idx) {
        pii x = split(n, idx - 1, 0);
        pii y = split(x.SS, 0, 0);

        rt = merge(x.FF, y.SS);
    }

    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }
        cout << n << " " << nodes[n].sv << " " << nodes[n].v2 << " " << nodes[n].lc << " " << nodes[n].rc << " " << nodes[n].sz << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
    }

    // updates & queries
    void apply(int n, ll b, ll c, int r) {
        if (b == 1 && c == 0 && r == 0) return;
        nodes[n].la = (nodes[n].la * b + c) % MOD;
        nodes[n].lm = (nodes[n].lm * b) % MOD;
        nodes[n].sv = (nodes[n].sv * b + 1ll * nodes[n].sz * c) % MOD;
        nodes[n].v = (nodes[n].v * b + c) % MOD;
        nodes[n].rev ^= r;
        if (r) swap(nodes[n].lc, nodes[n].rc);
    }

    void push(int n) {
        if (nodes[n].lc >= 0) apply(nodes[n].lc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        if (nodes[n].rc >= 0) apply(nodes[n].rc, nodes[n].lm, nodes[n].la, nodes[n].rev);
        nodes[n].la = 0, nodes[n].lm = 1, nodes[n].rev = 0;
    }

    void pull(int n) {
        nodes[n].sv = (nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0)) % MOD;
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
    }

    void update(int n, int l, int r, ll b, ll c, int rev) {
        pii x = split(n, l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        apply(y.FF, b, c, rev);
        push(y.FF);

        rt = merge(x.FF, merge(y.FF, y.SS));
    }

    ll query(int n, int l, int r) {
        pii x = split(n, l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        push(y.FF);
        ll v = nodes[y.FF].sv;
        rt = merge(x.FF, merge(y.FF, y.SS));
        return v;
    }
};

Treap tp;

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
        tp.insert(tp.rt, i, n);
    }

    while (Q--) {
        int t;
        cin >> t;
        if (t == 0) {
            int a, v;
            cin >> a >> v;
            a++;
            tp.insert(tp.rt, a, v);
        }
        if (t == 1) {
            int a;
            cin >> a;
            a++;
            tp.erase(tp.rt, a);
        }
        if (t == 2) {
            int l, r;
            cin >> l >> r;
            l++;
            tp.update(tp.rt, l, r, 1, 0, 1);
        }
        if (t == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            l++;
            tp.update(tp.rt, l, r, b, c, 0);
        }
        if (t == 4) {
            int l, r;
            cin >> l >> r;
            l++;
            // cout << l << " " << r << endl;
            cout << tp.query(tp.rt, l, r) << endl;
        }
    }

    return 0;
} 