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

int T;
int ans[1000010][30];
int s[1000];

int digsum(int a)
{
    int s = 0;
    for (int i = 0; i < 3; i++) 
    {
        s += a % 10;
        a /= 10;
    }
    return s;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 1000; i++) s[i] = digsum(i);

    for (int i = 0; i < 1000000; i++)
    {
        int d = abs(s[i % 1000] - s[i / 1000]);
        ans[i][d] = 1;
    }

    for (int j = 0; j < 30; j++) for (int i = 1; i < 1000000; i++)
        ans[i][j] += ans[i - 1][j];

    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        int l = abs(s[N % 1000] - s[N / 1000]);
        int a = 0;
        for (int i = 0; i < l; i++) 
            a += ans[N][i];
        cout << a << endl;
    }

    return 0;
} 