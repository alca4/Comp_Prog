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
int N, M;
map<int, int> a, b;

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        a[n]++;
    }
    for (int i = 1; i <= M; i++) {
        int n;
        cin >> n;
        b[n]++;
    }

    // for (pii p : a) cout << p.FF << " " << p.SS << endl;
    // cout << "a done" << endl;
    // for (pii p : b) cout << p.FF << " " << p.SS << endl;
    // cout << "b done" << endl;

    int has_ans = 0;
    while (!b.empty()) {
        if (a.empty()) break;

        pii bp = *b.rbegin();
        pii ap = *a.rbegin();
        // cout << bp.FF << endl;
        if (bp.FF < ap.FF) break;

        
        // cerr << "a guy is: " << ap.FF << endl;
        if (bp.FF == ap.FF) {
            // cout << "prepare to be annihilated " << endl;
            if (bp.SS < ap.SS) break;
            else {
                a.erase(--a.end());
                b.erase(--b.end());

                // cout << "annihilated " << bp.FF << endl;
                // cout << bp.SS << " " << ap.SS << endl;

                bp = pii(bp.FF, bp.SS - ap.SS);
                if (bp.SS) b.insert(bp);
            }
        } 
        else {
            // cout << "prepare to be split " << endl;
            b.erase(--b.end());
            b[bp.FF / 2] += bp.SS;
            b[bp.FF - bp.FF / 2] += bp.SS;
        }
    }

    if (a.empty() && b.empty()) has_ans = 1;

    if (has_ans) cout << "Yes" << endl;
    else cout << "No" << endl;

    a.clear();
    b.clear();
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