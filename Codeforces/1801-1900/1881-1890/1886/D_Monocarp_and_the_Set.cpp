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
ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) {
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
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 300010;
int N, Q;
int t[MAXN];

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        while (a < arr.size()) {
            multeq(arr[a], v);
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 1;
        while (a) {
            multeq(ans, arr[a]);
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {
        return divide(query(b), query(a - 1));
    }

    void clear() {
        arr.resize(0);
    }
};

void solve() {
    cin >> N >> Q;
    BIT bit(N - 1);
    int zeros = 0;
    for (int i = 0; i < N; i++) bit.arr[i] = 1;
    for (int i = 1; i < N; i++) {
        char c;
        cin >> c;
        if (c == '?') t[i] = 1;
        if (t[i]) {
            if (i == 1) zeros = 1;
            else bit.update(i, i - 1);
        }
    }

    // for (int i = 0; i < N; i++) cout << bit.arr[i] << " ";
    // cout << endl;

    cout << (zeros ? 0 : bit.query(1, N - 1)) << endl;

    while (Q--) {
        int n;
        char c;
        cin >> n >> c;

        if (c == '?') {
            if (!t[n]) {
                if (n == 1) zeros = 1;
                else bit.update(n, n - 1);
            }
        }
        else {
            if (t[n]) {
                if (n == 1) zeros = 0;
                else bit.update(n, divide(1, n - 1));
            }
        }

        if (c == '?') t[n] = 1;
        else t[n] = 0;
        cout << (zeros ? 0 : bit.query(1, N - 1)) << endl;
    }

    for (int i = 1; i < N; i++) t[i] = 0;
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
    while (T--) solve();

    return 0;
} 