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
ll ans, inc;
ll a[MAXN], b[MAXN];
vector<pll> up, down;

bool Comp(const pll& a, const pll& b)
{
    return (a.FF == b.FF ? a.SS > b.SS : a.FF < b.FF);
}

bool Comp2(const pll& a, const pll& b)
{
    return (a.SS - a.FF == b.SS - b.FF ? a < b : a.SS - a.FF < b.SS - b.FF);
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

    for (int i = 1; i <= N; i++) ans += abs(a[i] - b[i]);

    for (int i = 1; i <= N; i++)
    {
        if (a[i] < b[i]) up.pb({a[i], b[i]});
        else down.pb({b[i], a[i]});
    }

    sort(up.begin(), up.end(), Comp);
    sort(down.begin(), down.end(), Comp);

    multiset<pll, decltype(&Comp2)> itvs(&Comp2);

    int l = 0, u = -1;
    for (int i = 0; i < up.size(); i++)
    {
        while (u < ((int) down.size()) - 1 && down[u + 1].FF <= up[i].SS) 
        {
            itvs.insert(down[u + 1]);
            u++;
        }
        while (l <= u && down[l].SS < up[i].FF)
        {
            itvs.erase(itvs.find(down[l]));
            l++;
        }
        if (!itvs.empty()) 
        {
            inc = max(inc, 2 * (min(up[i].SS, itvs.rbegin()->SS) -
                                max(up[i].FF, itvs.rbegin()->FF)));
        }
    }

    cout << ans - inc << endl;
    return 0;
}