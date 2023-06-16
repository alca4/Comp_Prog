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

const int MAXN = 500010;
int N;
pii arr[MAXN];
multiset<int> must, can;

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i].FF >> arr[i].SS;

    for (int i = 1; i <= N; i++) must.insert(arr[i].SS);

    sort(arr + 1, arr + 1 + N);

    int ans = 2 * INF;
    for (int i = 1; i <= N; i++) {
        must.erase(must.find(arr[i].SS));
        if (i > 1) can.insert(arr[i - 1].SS);

        int t2 = 2 * INF;
        if (can.size()) {
            if (can.lower_bound(arr[i].FF) != can.end()) {
                int x = *can.lower_bound(arr[i].FF);
                if (abs(arr[i].FF - t2) > abs(arr[i].FF - x)) t2 = x; 
            }
            if (can.lower_bound(arr[i].FF) != can.begin()) {
                int x = *(--can.lower_bound(arr[i].FF));
                if (abs(arr[i].FF - t2) > abs(arr[i].FF - x)) t2 = x; 
            }
        }

        if (must.size())
            if (t2 < *must.rbegin() ||
                abs(arr[i].FF - t2) > abs(arr[i].FF - *must.rbegin())) t2 = *must.rbegin();
        ans = min(ans, abs(arr[i].FF - t2));
    }
    can.clear();
    must.clear();

    cout << ans << endl;

    for (int i = 1; i <= N; i++) arr[i] = {0, 0};
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