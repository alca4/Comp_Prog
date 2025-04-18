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
ll INF = 1000000000;
ll MOD = 998244353;

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

const int MAXN = 300010;
int N;
int arr[MAXN];
ll fact[MAXN];
ll factinv[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= 2 * N; i++) cin >> arr[i];

    fact[0] = factinv[0] = 1;
    for (int i = 1; i <= 2 * N; i++) fact[i] = mult(fact[i - 1], i);
    for (int i = 1; i <= 2 * N; i++) factinv[i] = divide(factinv[i - 1], i);

    sort(arr + 1, arr + 2 * N + 1);
    ll ans = 0;
    for (int i = 1; i <= N; i++) ans = sub(ans, arr[i]);
    for (int i = N + 1; i <= 2 * N; i++) ans = add(ans, arr[i]);

    cout << mult(ans, mult(fact[2 * N], mult(factinv[N], factinv[N]))) << endl;
    return 0;
} 