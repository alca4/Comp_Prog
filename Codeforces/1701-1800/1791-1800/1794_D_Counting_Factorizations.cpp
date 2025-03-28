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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
// ll MOD = LINF;
// ll MOD = 1000000007;
ll MOD = 998244353;

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
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

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

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 4050;
int N;
set<int> bases;
map<int, int> exps;
ll fact[1000010], factinv[1000010];
int arr[MAXN];
ll dp[MAXN][MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= 1000000; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[1000000] = divide(1, fact[1000000]);
    for (int i = 999999; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

int sieve[1000010];
vector<int> primes;
void get_primes()
{
    sieve[1] = 1;
    for (int i = 2; i <= 1000000; i++) if (!sieve[i])
    {
        primes.pb(i);
        for (int j = 2; i * j <= 1000000; j++) sieve[i * j] = 1;
    }
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    get_fact();
    get_primes();
    
    for (int i = 1; i <= 2 * N; i++) 
    {
        int n;
        cin >> n;
        exps[n]++;
        if (!sieve[n]) bases.insert(n); 
    }

    ll f = fact[N];
    for (auto n : exps) if (sieve[n.FF]) multeq(f, factinv[n.SS]);

    int S = bases.size();
    for (int i = 1; i <= S; i++)
    {
        arr[i] = *bases.begin();
        bases.erase(bases.begin());
    }

    dp[0][0] = 1;
    for (int i = 1; i <= S; i++) for (int j = 0; j <= min(i, N); j++)
    {
        dp[i][j] = mult(dp[i - 1][j], factinv[exps[arr[i]]]);
        if (j) addeq(dp[i][j], mult(dp[i - 1][j - 1], factinv[exps[arr[i]] - 1]));
    }

    cout << mult(f, dp[S][N]) << endl;
    return 0;
} 