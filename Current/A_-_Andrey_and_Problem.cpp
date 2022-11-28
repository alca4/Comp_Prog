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
ll MOD = 1000000007;

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
ll div(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

const int MAXN = 110;
int N;
ld arr[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ld ans = 0.0;
    sort(arr + 1, arr + 1 + N);
    for (int k = N; k >= 1; k--)
    {
        ld curans = 0;
        for (int i = k; i <= N; i++) 
        {
            ld inv = 1;
            for (int j = k; j <= N; j++) if (i != j) inv *= (1.0 - arr[j]);
            curans += inv * arr[i];
        }
        ans = max(ans, curans);
    }

    cout << fixed << setprecision(12) << ans << endl;
    return 0;
} 