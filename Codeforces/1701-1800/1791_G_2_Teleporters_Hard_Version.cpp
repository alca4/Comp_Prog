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
ll MOD = LINF;
// ll MOD = 1000000007;
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

const int MAXN = 200010;
int N, K;
int v[MAXN];
pll cost[MAXN];
// ll fact[MAXN], factinv[MAXN];

// ll choose(int a, int b)
// {
//     return mult(fact[a], mult(factinv[b], factinv[a - b]));
// }

// void get_fact(int x)
// {
//     fact[0] = 1;
//     for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
//     factinv[x] = divide(1, fact[x]);
//     for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
// }

void solve()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i];
        cost[i] = pii(v[i] + min(i, N + 1 - i), i);
    }

    sort(cost + 1, cost + 1 + N);

    for (int i = 1; i <= N; i++) cost[i].FF += cost[i - 1].FF;

    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        if (K - v[cost[i].SS] - cost[i].SS >= 0)
        {
            // cout << "start with " << i << endl;
            auto it = upper_bound(cost + 1, cost + 1 + N, pll(K - v[cost[i].SS] - cost[i].SS, INF)) - 1;
            if (distance(cost, it) >= i) 
            {
                it = upper_bound(cost + 1, cost + 1 + N, pll(K - cost[i].SS + min(cost[i].SS, N + 1 - cost[i].SS), INF)) - 1;
                // cout << distance(cost, it) << endl;
                maxeq(ans, distance(cost, it));
            }
            else 
            {
                // cout << distance(cost, it + 1) << endl;
                maxeq(ans, distance(cost, it + 1));
            }
        }
    }
    cout << ans << endl;

    for (int i = 1; i <= N; i++) v[i] = cost[i].FF = cost[i].SS = 0;
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