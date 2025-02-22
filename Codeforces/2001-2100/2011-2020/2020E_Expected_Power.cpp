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
ll MOD = 1000000007;

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
ll p[MAXN], pinv[MAXN];
ll ans[10][10][4];
ll t[4];

void reset_tc() {
    for (int i = 1; i <= N; i++) arr[i] = p[i] = pinv[i] = 0;

    for (int j = 0; j < 10; j++) for (int k = 0; k < 10; k++) 
        for (int h = 0; h < 4; h++) ans[j][k][h] = 0;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) cin >> p[i];
    for (int i = 1; i <= N; i++) p[i] = divide(p[i], 10000);
    for (int i = 1; i <= N; i++) pinv[i] = MOD + 1 - p[i];

    ll a = 0;
    for (int b1 = 0; b1 < 10; b1++) for (int b2 = 0; b2 < 10; b2++) {
        ans[b1][b2][0] = 1;
        for (int i = 1; i <= N; i++) {
            int v = ((arr[i] >> b1) & 1) | (((arr[i] >> b2) & 1) << 1);

            for (int h = 0; h < 4; h++)
                t[h] = (ans[b1][b2][h] * pinv[i] + ans[b1][b2][h ^ v] * p[i]) % MOD;
            
            for (int h = 0; h < 4; h++) ans[b1][b2][h] = t[h];
        }
        
        a += ans[b1][b2][3] * (1 << (b1 + b2));
        a %= MOD;
    }

    cout << a << endl;

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