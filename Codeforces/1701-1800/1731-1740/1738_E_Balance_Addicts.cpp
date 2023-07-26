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
ll MOD = 998244353;

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
int N;
ll arr[MAXN];
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

ll solve(int a, int b)
{
    int ta = a;
    while (ta <= b && arr[ta] == 0) ta++;
    int tb = b;
    while (tb >= a && arr[tb] == 0) tb--;

    if (ta == b + 1) return (power(2, b - a)) % MOD;

    int na = ta - a;
    int nb = b - tb;
    
    if (na != 0 && nb != 0)
    {
        ll coeff = 0;
        for (int i = 0; i <= min(na, nb); i++)
        {
            coeff += mult(choose(na, i), choose(nb, i));
            coeff %= MOD;
        }

        return mult(coeff, solve(ta, tb));
    }
    else
    {
        a = ta;
        b = tb;

        ll asum = arr[a];
        ll bsum = arr[b];

        while (asum != bsum)
        {
            if (asum < bsum) asum += arr[++a];
            else bsum += arr[--b];
        }
        if (a >= b) return 1;

        ta = a + 1;
        while (ta <= b && arr[ta] == 0) ta++;
        tb = b - 1;
        while (tb >= a && arr[tb] == 0) tb--;

        if (ta == b) return (power(2, b - a)) % MOD;

        na = ta - a - 1;
        nb = b - tb - 1;
        
        ll coeff = 0;
        for (int i = 1; i <= min(na, nb) + 1; i++)
        {
            coeff += mult(choose(na + 1, i), choose(nb + 1, i));
            coeff %= MOD;
        }

        return mult(coeff + 1, solve(ta, tb)); 
    }
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
        for (int i = 1; i <= N; i++) cin >> arr[i];

        fact[0] = factinv[0] = 1;
        for (int i = 1; i <= N; i++) fact[i] = mult(fact[i - 1], i);
        for (int i = 1; i <= N; i++) factinv[i] = divide(factinv[i - 1], i);

        cout << solve(1, N) << endl;
        for (int i = 1; i <= N; i++) arr[i] = 0;
    }
    return 0;
} 