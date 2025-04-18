/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
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
ll INF = 1000000000ll;
ll MOD = 1000000007ll;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
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

const int MAXN = 5010;
ll N, P;
ll fact[MAXN], factinv[MAXN], choose[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> P;
    MOD = P;
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i - 1], i);
    factinv[0] = 1;
    for (int i = 1; i <= N; i++) factinv[i] = divide(factinv[i - 1], i);

    ll ans = 0;
    for (int i = N / 2; i <= N - 2; i++) 
    {
        choose[0] = 1;
        for (int j = 1; j <= N - 2 - i; j++)
        {
            ll n = N - 2 - i;
            choose[j] = mult(fact[n], mult(factinv[j], factinv[n - j]));
        }
        for (int j = 0; j <= N - 2 - i; j++) 
            ans = add(ans, mult(mult(fact[i + j - 1], choose[j]), sub(mult(N / 2, 2), i)));
    }
    ans = mult(ans, N);
    
    if (N % 2 == 0) ans = add(ans, mult(N, fact[N - 2]));

    cout << ans << endl;
    return 0;
} 