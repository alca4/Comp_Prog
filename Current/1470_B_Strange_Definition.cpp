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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

ifstream fin(".in");
ofstream fout(".out");

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
ll sieve[1010];
vector<int> primes;
int arr[MAXN];

void solve()
{
    int N, Q;
    cin >> N;

    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) 
    {
        for (int j = 0; j < primes.size(); j++) 
            while (arr[i] % primes[j] == 0) arr[i] /= primes[j];
    }

    map<int, int> m;
    for (int i = 1; i <= N; i++) m[arr[i]]++;

    int ans_0 = 1;
    for (auto n : m) ans_0 = max(ans_0, n.SS);

    int ans_1 = 0;
    for (auto n : m) if (n.FF == 1 || n.SS % 2 == 0) ans_1 += n.SS;
    ans_1 = max(ans_0, ans_1);

    cin >> Q;
    while (Q--)
    {
        ll x;
        cin >> x;

        if (x == 0) cout << ans_0 << endl;
        else cout << ans_1 << endl;
    }
    for (int i = 1; i <= N; i++) arr[i] = 0;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 2; i <= 1000; i++)
    {
        if (!sieve[i])
        {
            primes.pb(i * i);
            for (int j = i; j <= 1000; j += i) sieve[j] = 1;
        }
    }

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 