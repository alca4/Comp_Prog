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

int N;
ll i, j, k;
ll tot;
ll dom;

void solve(int a, int b)
{
    if (a == b - 1) 
    {
        i = a;
        return;
    }
    if (a > b || a < 1 || b > N) return;
    ll left, right;
    int mid = (a + b) / 2;
    cout << "? " << a << " " << mid << endl;
    cin >> left;
    if (left == -1) return;

    if (left == 0) solve(mid, b);
    else solve(a, mid);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N;

        i = j = k = -1;

        cout << "? 1 " << N << endl;
        cin >> tot;
        if (tot == -1) return 0;
        dom = tot;
        solve(1, N);

        if (i == -1) return 0;

        cout << "? " << i + 1 << " " << N << endl;
        ll t;
        cin >> t;
        if (t == -1) return 0;

        j = tot - t + i + 1;

        ll a = 1;
        ll b = -2 * j + 1;
        ll c = 2 * j * j - 2 * i * j - 2 * j + i * i + i - 2 * tot;

        k = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

        cout << "! " << i << " " << j << " " << k << endl;
    }

    return 0;
} 

// 1000000000 1 999999999 1000000000