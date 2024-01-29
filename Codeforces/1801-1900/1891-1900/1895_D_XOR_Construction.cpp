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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
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
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N;
int arr[MAXN];

struct Trie {
    vector<int> trie;
    vector<int> lc;
    vector<int> rc;

    Trie() {
        create();
    }

    int create() {
        trie.pb(0);
        lc.pb(-1);
        rc.pb(-1);
        return trie.size() - 1;
    }
 
    void update(int i, int t, int cid) {
        trie[cid]++;
        if (t == -1) return;
        if ((1 << t) & i) {
            if (rc[cid] == -1) rc[cid] = create();
            update(i, t - 1, rc[cid]);
        }
        else {
            if (lc[cid] == -1) lc[cid] = create();
            update(i, t - 1, lc[cid]);
        }
    }

    int query(int a, int t, int cid) {
        if (t == -1) return 0;

        if ((1 << t) & a) {
            if (lc[cid] != -1 && trie[lc[cid]]) {
                return query(a, t - 1, lc[cid]) | (1 << t);
            }
            else if (rc[cid] != -1 && trie[rc[cid]]) {
                return query(a, t - 1, rc[cid]);
            }
            else return 0;
        }
        else {
            if (rc[cid] != -1 && trie[rc[cid]]) {
                return query(a, t - 1, rc[cid]) | (1 << t);
            }
            else if (lc[cid] != -1 && trie[lc[cid]]) {
                return query(a, t - 1, lc[cid]);
            }
            else return 0;
        }
    }
};

Trie t;

void solve() {
    cin >> N;
    for (int i = 1; i < N; i++) cin >> arr[i];

    for (int i = 1; i < N; i++) {
        arr[i] ^= arr[i - 1];
        t.update(arr[i], 20, 0);
    }

    for (int i = 0; i < N; i++) {
        if (t.query(i, 20, 0) < N) {
            cout << i << " ";
            for (int j = 1; j < N; j++) cout << (i ^ arr[j]) << " ";
            cout << endl;
            break;
        }
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 