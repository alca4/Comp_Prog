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

const int MAXN = 200010;
int N, M;
ll arr[MAXN];
ll need[MAXN];

void solve() {
    // cout << "=====" << endl;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) cin >> arr[i];
    arr[0] = LINF;
    arr[N + 1] = LINF;

    int stop = M + 1;
    for (int i = M + 1; i <= N + 1; i++) {
        if (i > stop) arr[i] += arr[i - 1];
        ll cost = 0;
        if (arr[i] >= 0) {
            for (int j = stop; j <= i; j++) 
                cost = min(cost, arr[j]);
            for (int j = stop; j <= i; j++) 
                need[j] = cost * -1;
            stop = i + 1;
        }
    }

    stop = M - 1;
    for (int i = M - 1; i >= 0; i--) {
        if (i < stop) arr[i] += arr[i + 1];
        ll cost = 0;
        if (arr[i] >= 0) {
            for (int j = stop; j >= i; j--) 
                cost = min(cost, arr[j]);
            for (int j = stop; j >= i; j--) 
                need[j] = cost * -1;
            stop = i - 1;
        }
    }

    int l = M - 1;
    int r = M + 1;
    while (l >= 0 && r <= N + 1 && (need[l] <= arr[M] || arr[M] >= need[r])) {
        if (need[l] <= arr[M]) {
            while (arr[l] < 0) l--;
            arr[M] += arr[l];
            l--;
        }
        else {
            while (arr[r] < 0) r++;
            arr[M] += arr[r];
            r++;
        }
    }

    if (l == -1 || r == N + 2) cout << "YES" << endl;
    else cout << "NO" << endl;

    for (int i = 0; i <= N + 1; i++) arr[i] = need[i] = 0;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 