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

const int MAXN = 110;
int N;
deque<int> dq;
vector<int> operations;

void solve() {
    cin >> N;
    int freq0 = 0, freq1 = 0;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;
        dq.pb(c - '0');
        if (c == '0') freq0++;
        if (c == '1') freq1++;
    }

    if (freq0 != freq1) cout << -1 << endl;
    else {
        int boost = 0;
        while (!dq.empty()) {
            while (!dq.empty() && dq.front() != dq.back()) {
                dq.pop_front();
                dq.pop_back();
                boost++;
            }

            if (!dq.empty()) {
                if (dq.front() == 0) {
                    operations.pb(boost + dq.size());
                    dq.pb(0);
                    dq.pb(1);
                }
                else { // dq.back() == 1
                    operations.pb(boost);
                    dq.push_front(1);
                    dq.push_front(0);
                }
            }
        }
        cout << operations.size() << endl;
        for (int n : operations) cout << n << " ";
        cout << endl;
    }

    operations.clear();
    dq.clear();
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