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

const int MAXN = 100010;
int N, Q;
int seq[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> seq[i];

    cin >> Q;
    while (Q--)
    {
        ll a[1000];
        ll x, y, k;
        cin >> x >> y >> k;

        if (x == 0 && y == 0)
        {
            cout << seq[1] << " " << seq[1] << endl;
            continue;
        }

        a[0] = x, a[1] = y;
        int sz = 1;
        while (abs(a[sz]) < 1000000000) a[++sz] = a[sz] * k + a[sz - 1];
        
        int highest = seq[1];
        int lowest = seq[1];

        int i = 1;
        while (i <= N && seq[i] <= sz) 
        {
            if (a[seq[i]] > a[highest]) highest = seq[i];
            if (a[seq[i]] < a[lowest]) lowest = seq[i];
            i++;
        }

        if (i <= N && a[sz] > 0) highest = seq[N];
        if (i <= N && a[sz] < 0) lowest = seq[N];

        cout << highest << " " << lowest << endl;
    }

    return 0;
} 