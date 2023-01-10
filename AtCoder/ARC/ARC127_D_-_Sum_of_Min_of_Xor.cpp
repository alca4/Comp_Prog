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

const int MAXN = 250010;
int N;
int a[MAXN], b[MAXN];

ll cont(int x, const vector<int>& v1, const vector<int>& v2)
{
    ll ret = 0;
    ll b1[18], b2[18];
    for (int i = 0; i < 18; i++) b1[i] = b2[i] = 0;
    for (int i = 0; i < v1.size(); i++) 
    {
        for (int j = 0; j < 18; j++) 
        {
            if (!x && ((a[v1[i]] & (1 << j)) > 0)) b1[j]++;
            if (x && ((b[v1[i]] & (1 << j)) > 0)) b1[j]++;
        }
    }
    for (int i = 0; i < v2.size(); i++) 
    {
        for (int j = 0; j < 18; j++) 
        {
            if (!x && ((a[v2[i]] & (1 << j)) > 0)) b2[j]++;
            if (x && ((b[v2[i]] & (1 << j)) > 0)) b2[j]++;
        }
    }

    ll s1 = v1.size();
    ll s2 = v2.size();
    for (int i = 0; i < 18; i++) ret += b1[i] * (s2 - b2[i]) * (1 << i);
    for (int i = 0; i < 18; i++) ret += b2[i] * (s1 - b1[i]) * (1 << i);
    return ret;
}

ll solve(vector<int>& ids, int bit)
{
    if (bit < 0) return cont(0, ids, ids) / 2;
    vector<int> zz, zo, oz, oo;

    for (int i = 0; i < ids.size(); i++)
    {
        int ai = (a[ids[i]] & (1 << bit));
        int bi = (b[ids[i]] & (1 << bit));
        
        if (ai && bi) oo.pb(ids[i]);
        if (ai && !bi) oz.pb(ids[i]);
        if (!ai && bi) zo.pb(ids[i]);
        if (!ai && !bi) zz.pb(ids[i]);
    }

    ll ret = 0;
    ret += cont(0, zo, zz);
    ret += cont(0, oz, oo);
    ret += cont(1, zo, oo);
    ret += cont(1, oz, zz);

    vector<int> z;
    for (int i = 0; i < zz.size(); i++) z.pb(zz[i]);
    for (int i = 0; i < oo.size(); i++) z.pb(oo[i]);
    vector<int> o;
    for (int i = 0; i < zo.size(); i++) o.pb(zo[i]);
    for (int i = 0; i < oz.size(); i++) o.pb(oz[i]);

    ret += solve(z, bit - 1);
    ret += solve(o, bit - 1);
    return ret;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];
    vector<int> ids;
    for (int i = 1; i <= N; i++) ids.pb(i);

    cout << solve(ids, 17) << endl;
    return 0;
} 