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
int N;
int arr[MAXN];
int v[MAXN];
vector<int> nbs[MAXN];

struct Node {
    int v, lc, rc, lazy;
};

struct Trie {
    Node trie[100 * MAXN];
    int cap = 0;

    int create() {
        trie[cap++] = {0, -1, -1, 0};
        return cap - 1;
    }

    void push(int n, int t) {
        if (trie[n].lazy == 0) return;

        if (trie[n].lazy & (1 << t)) swap(trie[n].lc, trie[n].rc);
        if (trie[n].lc != -1) trie[trie[n].lc].lazy ^= trie[n].lazy;
        if (trie[n].rc != -1) trie[trie[n].rc].lazy ^= trie[n].lazy;
        trie[n].lazy = 0;
    }

    void pull(int n) {
        trie[n].v = (trie[n].lc == -1 ? 0 : trie[trie[n].lc].v) + 
                    (trie[n].rc == -1 ? 0 : trie[trie[n].rc].v);
    }

    void insert(int n, int a, int t) {
        if (t == -1) {
            // cout << "inserting node at " << n << endl;
            trie[n].v = 1;
            return;
        }

        push(n, t);
        if (a & (1 << t)) {
            if (trie[n].rc == -1) {
                int s = create();
                trie[n].rc = s;
            }
            insert(trie[n].rc, a, t - 1);
        } else {
            if (trie[n].lc == -1) {
                int s = create();
                trie[n].lc = s;
            }
            insert(trie[n].lc, a, t - 1);
        }
        pull(n);        
    }

    int query(int n, int va, int t) {
        if (t == -1) return va;
        
        push(n, t);
        if (trie[n].lc != -1 && trie[trie[n].lc].v == (1 << t)) {
            if (trie[n].rc == -1) {
                int s = create();
                trie[n].rc = s;
            }
            return query(trie[n].rc, va | (1 << t), t - 1);
        } else {
            if (trie[n].lc == -1) {
                int s = create();
                trie[n].lc = s;
            }
            return query(trie[n].lc, va, t - 1);
        }
    }

    void merge(int n, int n2, int t) {
        if (t == -1) {
            trie[n].v = 1;
            return;
        }

        push(n, t);
        push(n2, t);
        if (trie[n2].lc != -1 && trie[trie[n2].lc].v > 0) {
            if (trie[n].lc == -1) {
                int s = create();
                trie[n].lc = s;
            }
            merge(trie[n].lc, trie[n2].lc, t - 1);
        } 
        if (trie[n2].rc != -1 && trie[trie[n2].rc].v > 0) {
            if (trie[n].rc == -1) {
                int s = create();
                trie[n].rc = s;
            }
            merge(trie[n].rc, trie[n2].rc, t - 1);
        }
        pull(n);
        pull(n2);
    }

    void print(int n, int v, int t) {
        if (t == -1) {
            cout << v << " ";
            return;
        }

        push(n, t);
        if (trie[n].lc != -1 && trie[trie[n].lc].v > 0) 
            print(trie[n].lc, v, t - 1);
        if (trie[n].rc != -1 && trie[trie[n].rc].v > 0) 
            print(trie[n].rc, v | (1 << t), t - 1);
        pull(n);
    }
};

Trie trie;
int key[MAXN];
int xorsum[MAXN];

void DFS(int a, int p) {
    if (nbs[a].size() == 1) {
        if (!arr[a]) trie.insert(key[a], arr[a], 30);
        v[a] = trie.query(key[a], 0, 30);
        // cout << "grundy value of " << a << " is " << v[a] << endl;
        // cout << "trie at " << a << " has size " << tries[key[a]].sz << endl;
        return;
    }

    for (int nb : nbs[a]) if (nb != p) {
        DFS(nb, a);
        xorsum[a] ^= v[nb];
    }

    for (int nb : nbs[a]) if (nb != p) {
        // cout << "applying lazy of " << (xorsum[a] ^ v[nb]) << " to " << nb << endl;
        trie.trie[key[nb]].lazy ^= xorsum[a] ^ v[nb];
        
        if (trie.trie[key[nb]].v > trie.trie[key[a]].v) swap(key[nb], key[a]);

        // cout << "merging " << a << " and " << nb << endl;
        trie.merge(key[a], key[nb], 30);
    }

    int va = 0;
    if (!arr[a]) trie.insert(key[a], xorsum[a], 30);
    v[a] = trie.query(key[a], 0, 30);
    // trie.print(key[a], 0, 25);
    // cout << endl;
    // cout << "grundy value of " << a << " is " << v[a] << endl;
    // cout << "trie at " << a << " has size " << tries[key[a]].sz << endl;
}

vector<int> cand;

void FindAnswer(int a, int p, int va) {
    va ^= xorsum[a];
    // cout << "at " << a << " value is " << va << endl;
    if (va == 0 && !arr[a]) cand.pb(a);
    for (int nb : nbs[a]) if (nb != p) {
        FindAnswer(nb, a, va ^ v[nb]);
    }
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    for (int i = 1; i <= N; i++) {
        int s = trie.create();
        key[i] = s;
    }

    DFS(1, 0);
    int va = 0;
    FindAnswer(1, 0, 0);
    sort(cand.begin(), cand.end());
    for (int n : cand) cout << n << endl;

    return 0;
} 