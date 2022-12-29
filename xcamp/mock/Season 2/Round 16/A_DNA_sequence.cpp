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
ll MOD = 1000000007;

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

int strs[2000010];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    vector<int> v;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == 'A') v.pb(0);
        if (str[i] == 'C') v.pb(1);
        if (str[i] == 'G') v.pb(2);
        if (str[i] == 'T') v.pb(3);
    }

    int N;
    cin >> N;

    int val = 0;
    for (int i = 0; i < N; i++) val += v[i] * (1 << (2 * i));
    strs[val]++;

    for (int i = N; i < v.size(); i++)
    {
        // cout << v[i] << endl;
        val /= 4;
        val += v[i] * (1 << (2 * N - 2));
        strs[val]++;
    }

    int ans = 0;
    for (int i = 0; i <= (1 << 2 * N); i++) ans = max(ans, strs[i]);
    cout << ans << endl;
    return 0;
} 