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
#define cout cerr
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
int N, Q;

#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sv;
    int v2;
    int ch[2], sz;
};

const int TSIZE = 5000010;
struct PTreap {
    Node nodes[TSIZE];
    int cap = 0;
    int op = 0;
    int rt[MAXN];

    PTreap() {rt[op++] = -1;}

    int copy(int n) {
        nodes[cap++] = nodes[n];
        return cap - 1;
    }

    int find(int n, int v, int before) {
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        int ret;
        if (nodes[n].lc >= 0 && v < d) ret = find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) ret = find(nodes[n].rc, v, d + 1);
        else ret = n;
        return ret;
    }

    pii split(int n, int v, int before, int c) {
        if (n >= 0) {
            int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
            int nn = (c ? copy(n) : n);
            if (v < d) {
                pii x = split(nodes[nn].lc, v, before, c);
                nodes[nn].lc = x.SS;
                pull(nn);
                return pii(x.FF, nn);
            }
            else {
                pii x = split(nodes[nn].rc, v, d + 1, c);
                nodes[nn].rc = x.FF;
                pull(nn);
                return pii(nn, x.SS);
            }
        }
        return pii(-1, -1);
    }

    int merge(int m, int n, int c) {
        if (m == -1) return n;
        if (n == -1) return m;

        int nn;
        if (nodes[m].v2 > nodes[n].v2) {
            nn = (c ? copy(m) : m);
            nodes[nn].rc = merge(nodes[nn].rc, n, c);
            pull(nn);
            return nn;
        } else {
            nn = (c ? copy(n) : n);
            nodes[nn].lc = merge(m, nodes[nn].lc, c);
            pull(nn);
            return nn;
        }
    }

    void insert(int n, int idx, int v, int c) {
        int nn = cap++;
        nodes[nn] = {v, v, rand(), -1, -1, 1};
        pii x = split(n, idx - 1, 0, c);
        if (c) rt[op++] = merge(merge(x.FF, nn, c), x.SS, c);
        else rt[op - 1] = merge(merge(x.FF, nn, c), x.SS, c);
    }

    void move(int n, int l, int r, int k) {
        if (k > r - l) {
            int l2 = l - k;
            int r2 = r - k;

            pii x = split(n, l - 1, 0, 1);
            pii y = split(x.SS, r - l, 0, 1);

            pii x2 = split(n, l2 - 1, 0, 1);
            pii y2 = split(x2.SS, r2 - l2, 0, 1);

            rt[op++] = merge(x.FF, merge(y2.FF, y.SS, 0), 0);
        } else {
            int l2 = l - k;
            int r2 = l - 1;

            pii x2 = split(n, l2 - 1, 0, 1);
            pii y2 = split(x2.SS, r2 - l2, 0, 1);

            int tree = copy(y2.FF);
            while (nodes[tree].sz < r - l + 1) {
                int cp = copy(tree);
                tree = merge(tree, cp, 1);
            }
            
            tree = split(tree, r - l, 0, 1).FF;
            assert(tree >= 0 && tree < cap);

            pii x = split(n, l - 1, 0, 1);
            pii y = split(x.SS, r - l, 0, 1);

            rt[op++] = merge(x.FF, merge(tree, y.SS, 0), 0);
        }
    }

    void revert(int n, int l, int r) {
        // cout << "reverting " << l << " " << r << endl;
        pii x = split(rt[0], l - 1, 0, 1);
        pii y = split(x.SS, r - l, 0, 1);

        pii x2 = split(n, l - 1, 0, 1);
        pii y2 = split(x2.SS, r - l, 0, 1);

        rt[op++] = merge(x2.FF, merge(y.FF, y2.SS, 0), 0);
        // cout << "done reverting" << endl;
    }

    void print(int n) {
        if (n == -1) {
            cout << -1 << endl;
            return;
        }
        cout << n << " " << nodes[n].v << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
    }

    // updates & queries

    void pull(int n) {
        // cout << n << endl;
        assert(n >= 0 && n < cap);
        nodes[n].sv = nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0);
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
    }

    ll query(int n, int l, int r) {
        pii x = split(n, l - 1, 0, 1);
        pii y = split(x.SS, r - l, 0, 1);

        ll v = nodes[y.FF].sv;
        rt[op++] = merge(x.FF, merge(y.FF, y.SS, 0), 0);
        return v;
    }

    void wipe() {
        for (int i = 0; i < cap; i++) nodes[i] = {0, 0, 0, 0, 0, 0};
        for (int i = 1; i < op; i++) rt[i] = 0;
        cap = 0;
        op = 1;
    }
};

PTreap tp;
int arr[MAXN], arr2[MAXN];

void clear() {
    for (int i = 2; i <= N; i++) 
        arr2[i] = tp.nodes[tp.find(tp.rt[tp.op - 1], i - 1, 0)].v;
    
    tp.wipe();
    for (int i = 1; i <= N; i++) tp.insert(tp.rt[0], i - 1, arr[i], 0);
    tp.insert(tp.rt[0], 0, arr2[1], 1);
    for (int i = 2; i <= N; i++) tp.insert(tp.rt[1], i - 1, arr2[i], 0);
}

int main() {
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
        tp.insert(tp.rt[0], i - 1, n, 0);
    }

    // cout << "#thewanakatree" << endl;
    // tp.print(tp.rt[tp.op - 1]);
    // cout << endl;

    for (int i = 1; i <= Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            cout << tp.query(tp.rt[tp.op - 1], l, r) << endl;
        }
        if (t == 2) {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            tp.move(tp.rt[tp.op - 1], l, r, k);
        }
        if (t == 3) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            tp.revert(tp.rt[tp.op - 1], l, r);
        }

        cout << "on query " << i << " capacity is: " << tp.cap << endl;

        if (i % 10 == 0) clear();

        // cout << "#thewanakatree" << endl;
        // tp.print(tp.rt[tp.op - 1]);
        // cout << endl;
    }

    return 0;
} 