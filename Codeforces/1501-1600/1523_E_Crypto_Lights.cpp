/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(ll a, ll b) {return (a + b) % MOD;}
ll mult(ll a, ll b) {return (a * b) % MOD;}

const int MAXN = 100010;
int N, K;
ll fact[MAXN];

ll modInv(int m)
{
    // cout << m << endl;
    ll binexp[33];
    binexp[0] = m;
    for (int i = 1; i <= 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    ll ans = 1;
    int a = MOD - 2;
    while (a)
    {
        ans = mult(ans, binexp[(int) log2(a & -a)]);
        a -= a & -a;
    }
    return ans;
}

ll choose(ll a, ll b) 
{
    if (a < b) return 0;
    if (b == 0) return 1;
    return mult(fact[a], modInv(mult(fact[b], fact[a - b])));
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> K;

    ll ans = 0;

    for (int i = 1; i <= N; i++)
    {
        if (N - (i - 1) * (K - 1) <= 0) break;
        ans = add(ans, mult(choose(N - (i - 1) * (K - 1), i), modInv(choose(N, i))));
    }

    cout << ans + 1 << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    fact[0] = 1;
    for (int i = 1; i <= 100000; i++) fact[i] = mult(fact[i - 1], i);

    int T;
    cin >> T;
    while (T--) solve();
}