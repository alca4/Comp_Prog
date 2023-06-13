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

const int MAXN = 200010;
int N, Q;

#define lc ch[0]
#define rc ch[1]

struct Node {
    ll v, sv;
    int ch[2], sz;
};

int rand32() {
    return (rand() << 16) | rand();
}

const int TSIZE = 1000010;
struct PTreap {
    Node nodes[TSIZE];
    int cap = 0;
    int op = 0;
    int rt[MAXN];
    ll vals[MAXN];

    int copy(int n) {
        nodes[cap++] = nodes[n];
        return cap - 1;
    }

    int find(int n, int v, int before) {
        // assert(n >= 0);
        // assert(n < cap);
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        int ret;
        if (nodes[n].lc >= 0 && v < d) ret = find(nodes[n].lc, v, before);
        else if (nodes[n].rc >= 0 && v > d) ret = find(nodes[n].rc, v, d + 1);
        else ret = n;
        return ret;
    }

    pii split(int n, int v, int before) {
        if (n >= 0) {
            // if (n >= cap) cout << "bad " << n << " " << cap << endl;
            // assert(n < cap);
            int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
            int nn = copy(n);
            // assert(nn >= 0);
            // assert(nn < cap);
            if (v < d) {
                pii x = split(nodes[nn].lc, v, before);
                nodes[nn].lc = x.SS;
                // assert(nn < cap);
                pull(nn);
                return pii(x.FF, nn);
            }
            else {
                pii x = split(nodes[nn].rc, v, d + 1);
                nodes[nn].rc = x.FF;
                // assert(nn < cap);
                pull(nn);
                return pii(nn, x.SS);
            }
        }
        return pii(-1, -1);
    }

    int merge(int m, int n) {
        if (m == -1) return n;
        if (n == -1) return m;

        // assert(m < cap);
        // assert(n < cap);
        int nn;
        if (rand32() % (nodes[m].sz + nodes[n].sz) < nodes[m].sz) {
            nn = copy(m);
            // assert(nn >= 0);
            // assert(nn < cap);
            nodes[nn].rc = merge(nodes[nn].rc, n);
        } else {
            nn = copy(n);
            // assert(nn >= 0);
            // assert(nn < cap);
            nodes[nn].lc = merge(m, nodes[nn].lc);
        }
        pull(nn);
        return nn;
    }

    void move(int n, int l, int r, int k) {
        if (k > r - l) {
            int l2 = l - k;
            int r2 = r - k;

            pii x = split(n, l - 1, 0);
            pii y = split(x.SS, r - l, 0);

            pii x2 = split(n, l2 - 1, 0);
            pii y2 = split(x2.SS, r2 - l2, 0);

            rt[op++] = merge(x.FF, merge(y2.FF, y.SS));
        } else {
            int l2 = l - k;
            int r2 = l - 1;

            pii x2 = split(n, l2 - 1, 0);
            pii y2 = split(x2.SS, r2 - l2, 0);

            int tree = copy(y2.FF);
            while (nodes[tree].sz < r - l + 1) {
                int cp = copy(tree);
                tree = merge(tree, cp);
            }
            
            tree = split(tree, r - l, 0).FF;

            pii x = split(n, l - 1, 0);
            pii y = split(x.SS, r - l, 0);

            rt[op++] = merge(x.FF, merge(tree, y.SS));
        }
    }

    void revert(int n, int l, int r) {
        pii x = split(rt[0], l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        pii x2 = split(n, l - 1, 0);
        pii y2 = split(x2.SS, r - l, 0);

        rt[op++] = merge(x2.FF, merge(y.FF, y2.SS));
    }

    void print(int n) {
        if (n == -1) {
            cerr << -1 << endl;
            return;
        }
        cerr << n << " " << nodes[n].v << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
        if (nodes[n].lc >= 0) print(nodes[n].lc);
        if (nodes[n].rc >= 0) print(nodes[n].rc);
    }

    // updates & queries

    void pull(int n) {
        nodes[n].sv = nodes[n].v +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sv : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sv : 0);
        nodes[n].sz = 1 +
                      (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0) +
                      (nodes[n].rc >= 0 ? nodes[nodes[n].rc].sz : 0);
    }

    ll query(int n, int l, int r) {
        pii x = split(n, l - 1, 0);
        pii y = split(x.SS, r - l, 0);

        ll v = nodes[y.FF].sv;
        rt[op++] = merge(x.FF, merge(y.FF, y.SS));
        return v;
    }

    void wipe() {
        cap = 0;
        op = 0;
    }

    void getArr(int n, int before) {
        if (n < 0) return;
        getArr(nodes[n].lc, before);
        int d = before + (nodes[n].lc >= 0 ? nodes[nodes[n].lc].sz : 0);
        vals[d + 1] = nodes[n].v;
        getArr(nodes[n].rc, d + 1);
    }

    int build(int l, int r) {
        if (l > r) return -1;
        int n = cap++;
        int mid = (l + r) / 2;
        nodes[n] = {vals[mid], vals[mid], -1, -1, 1};
        nodes[n].lc = build(l, mid - 1);
        nodes[n].rc = build(mid + 1, r);
        pull(n);
        return n;
    }
};

PTreap tp;
int arr[MAXN];

void clear() {
    tp.getArr(tp.rt[tp.op - 1], 0);
    for (int i = 1; i <= N; i++) arr[i] = tp.vals[i];
    tp.getArr(tp.rt[0], 0);
    tp.wipe();
    tp.rt[tp.op++] = tp.build(1, N);
    for (int i = 1; i <= N; i++) tp.vals[i] = arr[i];
    tp.rt[tp.op++] = tp.build(1, N);
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> tp.vals[i];
    tp.rt[tp.op++] = tp.build(1, N);
  
    // cout << "#thewanakatree" << endl;

    for (int i = 1; i <= Q; i++) {
        // cerr << "Query " << i << endl;
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

        if (i % 1000 == 0) clear();
        // cout << "#thewanakatree" << endl;
        // tp.print(tp.rt[tp.op - 1]);
        // cout << endl;
    }

    return 0;
} 