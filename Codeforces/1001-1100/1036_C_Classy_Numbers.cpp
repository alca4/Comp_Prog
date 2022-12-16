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
ll MOD = 2000000000000000000;

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

int num_nonzero(int i)
{
    int a = 0;
    while (i > 0)
    {
        if (i % 10 != 0) a++;
        i /= 10;
    }
    return a;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int cnt = 0;
    set<ll> s;
    for (ll i = 1; i < 1000; i++) s.insert(i);
    for (int i = 3; i <= 18; i++) // num digits
        for (ll a = 1; a <= 9; a++) for (ll b = 0; b <= 9; b++) for (ll c = 0; c <= 9; c++)
            for (int j = 0; j < i; j++) for (int k = 0; k < j; k++) if (j != k)
                s.insert(a * power(10, i) + b * power(10, j) + c * power(10, k));

    vector<ll> vec;
    for (ll n : s) vec.pb(n);

    int T;
    cin >> T;
    while (T--)
    {
        ll l, r;
        cin >> l >> r;
        cout << distance(lower_bound(vec.begin(), vec.end(), l), 
                         upper_bound(vec.begin(), vec.end(), r)) << endl;
    }
    return 0;
} 