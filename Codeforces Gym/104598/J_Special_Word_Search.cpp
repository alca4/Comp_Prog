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
ll MOD = 1000000007;

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
const int MAXM = 5010;
int N, M;
char grid[MAXN][MAXN];
string hen[MAXN];
string shu[MAXN];
string pie[MAXN * 2];
string na[MAXN * 2];
set<ll> tmp;
ll pow27[MAXN];
string words[MAXM];

void solve() {
    pow27[0] = 1;
    for (int i = 1; i <= 100; i++) pow27[i] = (pow27[i - 1] * 27);

    cin >> N >> M;

    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        cin >> grid[i][j];
    }
    
    for (int i = 1; i <= M; i++) {
        cin >> words[i];
        ll hval = 0;
        for (int j = 0; j < words[i].length(); j++) {
            hval += (words[i][j] - 'a' + 1) * pow27[j];
            // hval %= MOD;
        }
        tmp.insert(hval);
    }

    int ans = tmp.size();
    
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
        hen[i] += grid[i][j];
        shu[j] += grid[i][j];
        pie[i + j] += grid[i][j];
        na[i - j + N - 1] += grid[i][j];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll hval1 = 0;
            ll hval2 = 0;
            for (int k = 0; k < min(100, N); k++) {
                hval1 += (hen[i][(j + k) % N] - 'a' + 1) * pow27[k];
                hval2 += (hen[i][(j - k + N) % N] - 'a' + 1) * pow27[k];
                hval1 %= MOD;
                hval2 %= MOD;
                if (tmp.count(hval1)) tmp.erase(hval1);
                if (tmp.count(hval2)) tmp.erase(hval2);
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll hval1 = 0;
            ll hval2 = 0;
            for (int k = 0; k < min(100, N); k++) {
                hval1 += (shu[i][(j + k) % N] - 'a' + 1) * pow27[k];
                hval2 += (shu[i][(j - k + N) % N] - 'a' + 1) * pow27[k];
                // hval1 %= MOD;
                // hval2 %= MOD;
                if (tmp.count(hval1)) tmp.erase(hval1);
                if (tmp.count(hval2)) tmp.erase(hval2);
            }
        }
    }

    for (int i = 0; i < 2 * N - 1; i++) {
        for (int j = 0; j < pie[i].length(); j++) {
            ll hval1 = 0;
            ll hval2 = 0;
            for (int k = 0; k < min(100, (int) pie[i].length()); k++) {
                hval1 += (pie[i][(j + k) % pie[i].length()] - 'a' + 1) * pow27[k];
                hval2 += (pie[i][(j - k + pie[i].length()) % pie[i].length()] - 'a' + 1) * pow27[k];
                // hval1 %= MOD;
                // hval2 %= MOD;
                if (tmp.count(hval1)) tmp.erase(hval1);
                if (tmp.count(hval2)) tmp.erase(hval2);
            }
        }
    }
    for (int i = 0; i < 2 * N - 1; i++) {
        for (int j = 0; j < na[i].length(); j++) {
            ll hval1 = 0;
            ll hval2 = 0;
            for (int k = 0; k < min(100, (int) na[i].length()); k++) {
                hval1 += (na[i][(j + k) % na[i].length()] - 'a' + 1) * pow27[k];
                hval2 += (na[i][(j - k + na[i].length()) % na[i].length()] - 'a' + 1) * pow27[k];
                // hval1 %= MOD;
                // hval2 %= MOD;
                if (tmp.count(hval1)) tmp.erase(hval1);
                if (tmp.count(hval2)) tmp.erase(hval2);
            }
        }
    }

    cout << ans - (int) tmp.size() << endl;
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