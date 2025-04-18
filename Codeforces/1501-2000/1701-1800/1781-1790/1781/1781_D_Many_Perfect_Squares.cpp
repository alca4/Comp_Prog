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
ll MOD = LINF;

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

const int MAXN = 60;
int N;
int arr[MAXN];

int sieve[1000010];
vector<int> primes;
void get_primes(int x)
{
    sieve[1] = 1;
    for (int i = 2; i <= x; i++) if (!sieve[i])
    {
        primes.pb(i);
        for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
    }
}

ll rand32() {return abs((rand() << 16) | rand());}
ll rand64() {return abs((rand32() << 16) | rand32());}

int test(ll x) {
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        ll a = sqrtl(x + arr[i]);
        ans += (a * a == x + arr[i]);
    }
    return ans;
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    int ans = 1;
    for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
        int d = arr[j] - arr[i];
        for (int k = 1; k * k <= d; k++) {
            if (k % 2 == (d / k) % 2) {
                ll m = (k + d / k) / 2;
                ll x = m * m - arr[j];
                if (x < 0) continue;
                ans = max(ans, test(x));
            }
        }
    }

    cout << ans << endl;

    for (int i = 1; i <= N; i++) arr[i] = 0;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    get_primes(1000000);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 