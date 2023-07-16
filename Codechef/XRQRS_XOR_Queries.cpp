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
typedef complex<ld> cd;

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
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
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

const int MAXN = 500010;
int N;

struct Trie {
    vector<int> nodes, lc, rc;
    vector<int> roots;

    Trie() {
        roots.pb(create());
    }

    int create() {
        nodes.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return nodes.size() - 1;
    }

    int get(int a) {
        if (a == -1) return 0;
        return nodes[a];
    }

    int get(int a, int dir) {
        if (a == -1) return 0;
        if (dir == 0) {
            if (lc[a] == -1) return 0;
            else {
                // cout << lc[a] << " is " << nodes[lc[a]] << endl;
                return nodes[lc[a]];
            }
        }
        else {
            if (rc[a] == -1) return 0;
            else {
                // cout << rc[a] << " is " << nodes[rc[a]] << endl;
                return nodes[rc[a]];
            }
        }
    }

    int update(int a, int cid, int t = 30) {
        int nn = create();
        nodes[nn] = nodes[cid];
        lc[nn] = lc[cid];
        rc[nn] = rc[cid];
        // cout << "created new node " << nn << " with " << lc[nn] << " " << rc[nn] << endl;
        if (t == -1) {
            nodes[nn]++;
            return nn;
        }

        if (a & (1 << t)) {
            if (rc[nn] == -1) rc[nn] = create();
            rc[nn] = update(a, rc[nn], t - 1);
        }
        else {
            if (lc[nn] == -1) lc[nn] = create();
            lc[nn] = update(a, lc[nn], t - 1);
        }

        nodes[nn] = get(nn, 0) + get(nn, 1);
        // cout << nn << " " << nodes[nn] << " " << lc[nn] << " " << rc[nn] << endl;
        return nn;
    }

    int kth(int k, int n1, int n2, int t = 30) {
        if (t == -1) return 0;

        if (n1 == -1) {
            if (lc[n2] != -1 && get(n2, 0) >= k) 
                return kth(k, -1, lc[n2], t - 1);
            
            if (rc[n2] != -1 && get(n2, 1) >= k - get(n2, 0)) {
                return kth(k - get(n2, 0), -1, rc[n2], t - 1) | (1 << t);
            }

            assert(0);
            return -1;
        }

        if (lc[n2] != -1 && get(n2, 0) - get(n1, 0) >= k) {
            return kth(k, lc[n1], lc[n2], t - 1);
        }
        if (rc[n2] != -1 && get(n2, 1) - get(n1, 1) >= k - get(n2, 0) + get(n1, 0)) {
            return kth(k - get(n2, 0) + get(n1, 0), rc[n1], rc[n2], t - 1) | (1 << t);
        }

        assert(0);
        return -1;
    }

    int num_less(int v, int n1, int n2, int t = 30) {
        if (n2 == -1) return 0;
        if (t == -1) return get(n2) - get(n1);

        if (n1 == -1) {
            if (v & (1 << t)) {
                return num_less(v, -1, rc[n2], t - 1) + get(n2, 0);
            }
            else return num_less(v, -1, lc[n2], t - 1);
        }

        if (v & (1 << t)) {
            return num_less(v, rc[n1], rc[n2], t - 1) + get(n2, 0) - get(n1, 0);
        }
        else return num_less(v, lc[n1], lc[n2], t - 1);
    }

    int best_xor(int v, int n1, int n2, int t = 30) {
        if (t == -1) return 0;

        if (n1 == -1) {
            if ((v & (1 << t))) {
                if (get(n2, 0)) {
                    return best_xor(v, -1, lc[n2], t - 1);
                }
                if (get(n2, 1)) {
                    return best_xor(v, -1, rc[n2], t - 1) | (1 << t);
                }
            }
            else {
                if (get(n2, 1)) {
                    return best_xor(v, -1, rc[n2], t - 1) | (1 << t);
                }
                if (get(n2, 0)) {
                    return best_xor(v, -1, lc[n2], t - 1);
                }
            }
            assert(0);
            return -1;
        }

        if ((v & (1 << t))) {
            if (get(n2, 0) - get(n1, 0)) {
                return best_xor(v, lc[n1], lc[n2], t - 1);
            }
            if (get(n2, 1) - get(n1, 1)) {
                return best_xor(v, rc[n1], rc[n2], t - 1) | (1 << t);
            }
        }
        else {
            if (get(n2, 1) - get(n1, 1)) {
                return best_xor(v, rc[n1], rc[n2], t - 1) | (1 << t);
            }
            if (get(n2, 0) - get(n1, 0)) {
                return best_xor(v, lc[n1], lc[n2], t - 1);
            }
        }
        assert(0);
        return -1;
    }
};

Trie trie;

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    int sz = 0;
    while (N--) {
        int t;
        cin >> t;
        if (t == 0) {
            int x;
            cin >> x;
            sz++;
            trie.roots.pb(trie.update(x, trie.roots[sz - 1]));
        }
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << trie.best_xor(x, trie.roots[l - 1], trie.roots[r]) << endl;
        }
        if (t == 2) {
            int x;
            cin >> x;
            sz -= x;
            for (int i = 0; i < x; i++) trie.roots.pop_back();
        }
        if (t == 3) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << trie.num_less(x, trie.roots[l - 1], trie.roots[r]) << endl;
        }
        if (t == 4) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << trie.kth(x, trie.roots[l - 1], trie.roots[r]) << endl;
        }
    }

    return 0;
} 