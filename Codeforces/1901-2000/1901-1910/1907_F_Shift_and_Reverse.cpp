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

const int MAXN = 0;
int N;
deque<int> dq;

void solve() {
    cin >> N;
    int minval = INF, maxval = 0;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        dq.pb(n);
        minval = min(minval, n);
        maxval = max(maxval, n);
    }
    
    int ans = INF;

    int cnt = 0;
    while (!((dq.front() == minval && dq.back() == maxval) ||
             (dq.front() == maxval && dq.back() == minval)) && cnt < N) {
        // cout << dq.front() << " " << dq.back() << endl;
        dq.push_front(dq.back());
        dq.pop_back();
        cnt++;
    }
    // cout << "count is: " << cnt << endl;

    if (dq.front() == minval && dq.back() == maxval) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (dq[i] < dq[i - 1]) ok = 0;
        }
        if (ok) ans = min(ans, cnt);
    }
    else if (dq.front() == maxval && dq.back() == minval) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (dq[i] > dq[i - 1]) ok = 0;
        }
        if (ok) ans = min(ans, cnt + 1);
    }

    // cout << ans << endl;

    while (cnt--) {
        dq.pb(dq.front());
        dq.pop_front();
    }
    // cout << ans << endl;

    cnt = 0;
    while (!((dq.front() == minval && dq.back() == maxval) ||
             (dq.front() == maxval && dq.back() == minval)) && cnt < N) {
        // cout << dq.front() << " " << dq.back() << endl;
        dq.pb(dq.front());
        dq.pop_front();
        cnt++;
    }
    // cout << dq.front() << " " << dq.back() << endl;

    if (dq.front() == minval && dq.back() == maxval) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (dq[i] < dq[i - 1]) ok = 0;
        }
        if (ok) ans = min(ans, cnt + 2);
    }
    else if (dq.front() == maxval && dq.back() == minval) {
        int ok = 1;
        for (int i = 1; i < N; i++) {
            if (dq[i] > dq[i - 1]) ok = 0;
        }
        if (ok) ans = min(ans, cnt + 1);
    }

    cout << (ans == INF ? -1 : ans) << endl;

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