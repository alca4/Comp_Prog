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
ll INF = 2000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

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
        int id = (int) log2(n & -n);
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

const int MAXN = 5010;
int N, M;
int arr[MAXN];
int h[MAXN], c[MAXN];
ll fact[MAXN], factinv[MAXN];
ll dp[MAXN], dp2[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

void solve()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) cin >> c[i];
    for (int i = 1; i <= M; i++) cin >> h[i];
    
    M++;
    arr[0] = M;

    for (int i = 1; i <= M - 1; i++) dp[i] = LINF;
    for (int i = 1; i <= M - 1; i++) dp2[i] = LINF;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++) 
        {
            if (arr[i] != arr[i - 1]) dp2[j] += c[arr[i]];
            else dp2[j] += h[arr[i]];
        }
        
        ll hmm = 9ll * LINF;
        for (int j = 1; j <= M; j++) mineq(hmm, dp[j]);
        mineq(dp2[arr[i - 1]], min(dp[arr[i]] + h[arr[i]], hmm + c[arr[i]]));
        for (int j = 1; j <= M; j++) dp[j] = dp2[j];

        for (int i = 1; i <= M; i++) cout << dp[i] << " ";
        cout << endl;
    }

    ll best = LINF;
    for (int j = 1; j <= M; j++) mineq(best, dp[j]);
    cout << best << endl;
    
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i <= M; i++) c[i] = h[i] = 0;
    for (int i = 1; i <= M; i++) dp[i] = dp2[i] = 0;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 