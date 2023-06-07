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

const int MAXN = 0;
int N;

#define lc ch[0]
#define rc ch[1]

struct Node {
    int v, p, pp, rev, ch[2], sz;
};
struct LCT {
    Node nodes[MAXN];
    int cap = 0;
 
    LCT() {insert(0, 0, 0);}
 
    // maintaining splay tree structure
    int dir(int n) {
        if (nodes[n].p == -1) return -1;
        return nodes[nodes[n].p].rc == n;
    }
 
    void rotate(int n) {
        int p = nodes[n].p;
        int dn = dir(n);
        int dp = dir(p);
        push(p);
        push(n);
        int same = nodes[n].ch[dn];
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
        nodes[n2].pp = n;
        nodes[n].rc = -1;
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
        pull(n);
        return n;
    }
 
    void insert(int v) {
        nodes[cap++] = {v, -1, -1, 0, -1, -1, 1};
    }

    void erase(int n, int idx) {
        pii x = split(n, idx - 1);
        pii y = split(x.SS, 0);
        merge(x.FF, y.SS);
    }
 
    // void print(int n) {
    //     if (n == -1) {
    //         cout << -1 << endl;
    //         return;
    //     }
    //     cout << n << " " << nodes[n].sv << " " << nodes[n].lc << " " << nodes[n].rc << endl;
 
    //     if (nodes[n].lc >= 0) print(nodes[n].lc);
    //     if (nodes[n].rc >= 0) print(nodes[n].rc);
    // }

    void apply(int n, int r) {
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
    }

    // lct methods
    void access(int n) {
        int tn = n;
        splay(n);
        while (nodes[n].pp != -1) {
            int p = nodes[n].pp;
            splay(p);
            if (nodes[p].rc >= 0) {
                int r = nodes[p].rc;
                nodes[r].p = -1;
                nodes[r].pp = p;
            }
            nodes[p].rc = n;
            nodes[n].pp = -1;
            n = p;
        }
        splay(tn);
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
        reroot(m);
        nodes[m].pp = n;
    }

    void cut(int m, int n) {
        reroot(m);
        access(n);
        nodes[n].lc = -1;
        nodes[m].p = -1;
        nodes[m].pp = n;
    }

    // ll query(int m, int n) {
    //     reroot(m);
    //     access(n);
    // }
};

LCT lct;

int main() {
    lct.insert(1);
    lct.insert(2);
    lct.insert(3);
}