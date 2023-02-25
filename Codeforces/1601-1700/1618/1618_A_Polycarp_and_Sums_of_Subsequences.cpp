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
        vector<int> arr;
        multiset<int> vals;
        for (int i = 0; i < 7; i++)
        {
            int n;
            cin >> n;
            arr.pb(n);
            vals.insert(n);
        }

        sort(arr.begin(), arr.end());

        int x = arr[0], y = arr[1], z = arr[2];
        vals.erase(x);
        vals.erase(y);
        vals.erase(z);
        if (vals.count(x + y)) vals.erase(vals.find(x + y));
        if (vals.count(z + y)) vals.erase(vals.find(y + z));
        if (vals.count(x + z)) vals.erase(vals.find(x + z));
        if (vals.count(x + y + z)) vals.erase(vals.find(x + z + y));
        
        if (vals.empty()) cout << x << " " << y << " " << z << endl;
        else cout << arr[0] << " " << arr[1] << " " << arr[3] << endl;
    }

    return 0;
} 