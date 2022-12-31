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

const int MAXN = 200010;
int N;
vector<ll> vec;
int cnt[65];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) 
    {
        int x;
        cin >> x;
        vec.pb(x);
    }

    sort(vec.rbegin(), vec.rend());

    int ok = 1;
    for (int i = N - 2; i >= 0; i--) 
    {
        if (vec[i] % vec[N - 1]) ok = 0;
        vec[i] /= vec[N - 1];
    }
    vec[N - 1] = 1;
    for (int i = N - 1; i >= 0; i--) 
    {
        if (vec[i] != (vec[i] & -vec[i])) ok = 0;
        vec[i] = log2(vec[i]);
    }

    for (int i = 0; i < N; i++) cnt[vec[i]]++;

    int ans = 0;
    for (int i = 0; i <= 64; i++)
    {
        int rem = 0;
        for (int i = 0; i <= 64; i++) rem += cnt[i];
        if (rem == 1) break;
        ans += cnt[i] % 2;
        cnt[i + 1] += (cnt[i] + 1) / 2;
        cnt[i] = 0;
        rem -= (cnt[i] + 1) / 2;
    }

    if (ok) cout << ans << endl;
    else cout << -1 << endl;
    return 0;
} 