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

Tooting Bec
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
ll MOD2 = 998244853;

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

ll check(int a) {
    // cout << "checking " << a << endl;
    pll hash = pll(LINF, LINF);
    vector<int> zeroseq;
    int zeros = 0;
    for (int i = 1; i <= N; i++) {
        if (arr[i]) {
            pll thash = pll(0, 0);
            ll mult = 1, mult2 = 1;
            int nz = 0;
            // cout << i << " ";
            while (nz < a) {
                if (arr[i]) nz++;

                thash.FF = (thash.FF + (mult * arr[i])) % MOD;
                thash.SS = (thash.SS + (mult2 * arr[i])) % MOD2;
                mult = (mult * 26) % MOD;
                mult2 = (mult2 * 26) % MOD2;

                i++;
            }
            i--;
            // cout << i << endl;

            if (hash == pll(LINF, LINF)) hash = thash;
            else if (thash != hash) {
                // cout << "NO TRUST" << endl;
                return 0;
            }

            zeroseq.pb(zeros);
            zeros = 0;
        }
        else {
            // cout << "NOT SUCCESSFUL" << endl;
            zeros++;
        }
    }
    zeroseq.pb(zeros);

    // cout << "zeros: ";
    // for (int n : zeroseq) cout << n << " ";
    // cout << endl;

    int minzeromid = INF;
    for (int i = 1; i + 1 < zeroseq.size(); i++) minzeromid = min(minzeromid, zeroseq[i]);

    ll ans = 0;
    if (minzeromid == INF) ans = 1ll * (zeroseq[0] + 1) * (zeroseq.back() + 1);
    else {
        for (int i = 0; i <= min(zeroseq[0], minzeromid); i++) {
            ans += min(minzeromid - i, zeroseq.back()) + 1;
        }
    }
    // cout << "gives us " << ans << endl;
    return ans;
}

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

void solve() {
    string str;
    cin >> str;
    N = str.length();
    for (int i = 1; i <= N; i++) arr[i] = (str[i - 1] - 'a');

    int nonzero = 0;
    for (int i = 1; i <= N; i++) if (arr[i]) nonzero++;

    ll ans = 0;
    for (int i = 1; i * i <= nonzero; i++) if (nonzero % i == 0) {
        ans += check(i);
        if (i != nonzero / i) ans += check(nonzero / i);
    }

    if (nonzero == 0) cout << N - 1 << endl;
    else cout << ans << endl;

    reset_tc();
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