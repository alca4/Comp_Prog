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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
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

const int MAXN = 2010;
int N;
pii arr[MAXN];
vector<int> nbs[MAXN];
int dp[MAXN];

void solve() {
    // cout << "==========" << endl;
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i].FF >> arr[i].SS;

    sort(arr + 1, arr + 1 + N);

    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (arr[j].FF <= arr[i].SS) {
                nbs[i].pb(j);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        int bad = 0;
        vector<int> cand;
        for (int j = i - 1; j >= 1; j--) {
            if (nbs[j].size()) {
                // cout << j << " can go to " << i << endl;
                if (nbs[j].back() > i) {
                    bad = 1;
                    break;
                }
                if (nbs[j].back() == i) cand.pb(j);
            }
        }

        dp[i] = dp[i - 1];
        for (int n : cand)
            dp[i] = max(dp[i], dp[n - 1] + 2);
    }

    cout << N - dp[N] << endl;
    for (int i = 1; i <= N; i++) nbs[i].clear();
    for (int i = 1; i <= N; i++) arr[i] = {0, 0};
    for (int i = 1; i <= N; i++) dp[i] = 0;
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 