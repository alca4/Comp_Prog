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

const int MAXN = 100010;
int N;
int arr[MAXN];
int id[MAXN];
map<int, int> mappy;

struct BIT {
    vector<ll> arr;

    BIT() {arr.resize(0);}
    BIT(int n) {arr.resize(n + 1);}

    void update(int a, ll v) {
        while (a < arr.size()) {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a) {
        ll ans = 0;
        while (a) {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }

    ll query(int a, int b) {
        if (a > b) return 0;
        return query(b) - query(a - 1);
    }

    void clear() {
        arr.resize(0);
    }
};

BIT bit;

void solve() {
    cin >> N;
    bit = BIT(N);
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        mappy[n] = i;
    }

    int ok = 1;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        if (!mappy.count(arr[i])) ok = 0;
        arr[i] = mappy[arr[i]];
        id[arr[i]] = i;
        // cout << arr[i] << " ";
        bit.update(i, 1);
    }
    // cout << endl;

    ll eek = 0;
    if (ok) {
        for (int i = N; i >= 1; i--) {
            int rid = bit.query(1, id[i]);
            eek += max(0, i - rid);
            // eek += bit.query(id[i] + 1, i) + bit.query(1, id[i]);
            // // cout << i << " " << min(id[i], i) - bit.query(1, id[i]) 
            // //      << " before " << bit.query(id[i] + 1, i) << " after " << endl;
            bit.update(id[i], -1);
            // cout << eek << endl;
        }
    }

    if (ok && eek % 2 == 0) cout << "YES" << endl;
    else cout << "NO" << endl;

    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i <= N; i++) id[i] = 0;
    mappy.clear();
    bit.clear();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 