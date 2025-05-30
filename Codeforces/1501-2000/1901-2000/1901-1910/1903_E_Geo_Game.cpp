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
// #define endl "\n"
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

const int MAXN = 0;
int N;
set<int> even;
set<int> odd;

void solve() {
    cin >> N;
    assert(N != -1);
    int cur = 0;
    int a, b;
    cin >> a >> b;
    cur = (a + b) & 1;
    for (int i = 1; i <= N; i++) {
        cin >> a >> b;
        if ((a + b) & 1) odd.insert(i);
        else even.insert(i);
    }

    if (cur) swap(even, odd);
    
    if (odd.size() > even.size()) {
        cout << "Second" << endl;
        for (int i = 1; i <= N; i++) {
            if (i & 1) {
                int n;
                cin >> n;
                assert(n != -1);
                if (odd.count(n)) odd.erase(n);
                else even.erase(n);
            }

            else {
                if (even.size()) {
                    cout << *even.begin() << endl;
                    even.erase(even.begin());
                }
                else {
                    cout << *odd.begin() << endl;
                    odd.erase(odd.begin());
                }
            }
        }
    }
    else {
        cout << "First" << endl;
        for (int i = 1; i <= N; i++) {
            if (i & 1) {
                if (odd.size()) {
                    cout << *odd.begin() << endl;
                    odd.erase(odd.begin());
                }
                else {
                    cout << *even.begin() << endl;
                    even.erase(even.begin());
                }
            }

            else {
                int n;
                cin >> n;
                assert(n != -1);
                if (odd.count(n)) odd.erase(n);
                else even.erase(n);
            }
        }
    }

    even.clear(), odd.clear();
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