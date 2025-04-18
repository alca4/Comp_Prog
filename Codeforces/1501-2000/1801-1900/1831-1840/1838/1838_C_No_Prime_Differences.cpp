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

const int MAXN = 0;
int N, M;
vector<vector<int>> vec;

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

void solve() {
    cin >> N >> M;
    vec.resize(N);
    for (int i = 0; i < N; i++) vec[i].resize(M);

    if (sieve[M]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) vec[i][j] = j + i * M + 1;
        }
    }
    else if (sieve[N]) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) vec[i][j] = i + j * N + 1;
        }
    }
    else {
        vec[0].clear();
        vector<int> tmp;
        for (int i = 0; i < N; i += 2) tmp.pb(i * M + 1);
        tmp.pb((N - 4) * M + 1);
        tmp.pb((N - 2) * M + 1);
        for (int i = N - 6; i >= 0; i -= 2) tmp.pb(i * M + 1);
        for (int i = 0; i < N; i++) {
            vec[i][0] = tmp[i];
            for (int j = 1; j < M; j++) vec[i][j] = vec[i][j - 1] + 1;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << vec[i][j] << " ";
        cout << endl;
    }

    vec.clear();
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
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