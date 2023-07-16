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

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 20;
int N;

int tx, ty;
vector<pii> i1;
vector<pii> i2;
pii dp[(1 << MAXN)];
vector<pll> f1[MAXN + 1], f2[MAXN + 1];
ll ans[2 * MAXN + 1];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> tx >> ty;
    for (int i = 0; i < N; i++) {
        pii p;
        cin >> p.FF >> p.SS;
        if (i < MAXN) i1.pb(p);
        else i2.pb(p);
    }

    dp[0] = pll(0, 0);
    for (int i = 0; i < (1 << i1.size()); i++) {
        for (int j = 0; j < i1.size(); j++) if (i & (1 << j)) {
            dp[i] = {dp[i ^ (1 << j)].FF + i1[j].FF,
                     dp[i ^ (1 << j)].SS + i1[j].SS};
            break;
        }
        f1[__builtin_popcount(i)].pb(dp[i]);
    }

    for (int i = 0; i < (1 << i1.size()); i++) dp[i] = {0, 0};

    // cout << i2.size() << endl;
    dp[0] = pll(tx, ty);
    for (int i = 0; i < (1 << i2.size()); i++) {
        for (int j = 0; j < i2.size(); j++) if (i & (1 << j)) {
            dp[i] = {dp[i ^ (1 << j)].FF - i2[j].FF,
                     dp[i ^ (1 << j)].SS - i2[j].SS};
            break;
        }
        f2[__builtin_popcount(i)].pb(dp[i]);
    }

    for (int i = 0; i <= MAXN; i++) {
        sort(f1[i].begin(), f1[i].end());
        sort(f2[i].begin(), f2[i].end());
    }

    for (int i = 0; i <= MAXN; i++) for (int j = 0; j <= MAXN; j++) {
        int l = 0, r = 0;
        while (l < f1[i].size() && r < f2[j].size()) {
            if (f1[i][l] == f2[j][r]) {
                pll v = f1[i][l];
                ll dl = 0;
                while (l + dl < f1[i].size() && f1[i][l + dl] == v) dl++;
                ll dr = 0;
                while (r + dr < f2[j].size() && f2[j][r + dr] == v) dr++;
                ans[i + j] += dl * dr;
                l += dl;
                r += dr;
            }
            else if (f1[i][l] < f2[j][r]) l++;
            else r++;
        }
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << endl;

    return 0;
} 