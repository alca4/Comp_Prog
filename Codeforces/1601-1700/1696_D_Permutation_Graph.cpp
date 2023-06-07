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

const int MAXN = 250010;
int N;
int arr[MAXN];
int loc[MAXN];
int o[MAXN][2], n[MAXN][2];

int dist(int l, int r, int t) {
    if (l >= r) return 0;
    // cout << "solving for " << l << " " << r << endl;
    if (l == 1) {
        int id = loc[o[r][t]];
        if (id == r) return 1;
        return dist(1, loc[o[r][t]], 1 - t) + 1;
    } 
    else {
        int id = loc[n[l][t]];
        if (id == l) return 1;
        return dist(loc[n[l][t]], N, 1 - t) + 1;
    }
}

void solve() {
    // cout << "======" << endl;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        loc[arr[i]] = i;
    }
    o[1][0] = o[1][1] = arr[1];
    n[N][0] = n[N][1] = arr[N];
    for (int i = 2; i <= N; i++) {
        o[i][0] = min(arr[i], o[i - 1][0]);
        o[i][1] = max(arr[i], o[i - 1][1]);
    }
    for (int i = N - 1; i >= 1; i--) {
        n[i][0] = min(arr[i], n[i + 1][0]);
        n[i][1] = max(arr[i], n[i + 1][1]);
    }

    int minloc = loc[o[N][0]];
    int maxloc = loc[o[N][1]];

    if (N == 1) cout << 0 << endl;
    else if (maxloc < minloc) 
        cout << dist(1, maxloc, 0) + 1 + dist(minloc, N, 1) << endl;
    else 
        cout << dist(1, minloc, 1) + 1 + dist(maxloc, N, 0) << endl;
    
    for (int i = 1; i <= N; i++)
        arr[i] = o[i][0] = o[i][1] = n[i][0] = n[i][1] = loc[i] = 0;
}

int main()
{
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