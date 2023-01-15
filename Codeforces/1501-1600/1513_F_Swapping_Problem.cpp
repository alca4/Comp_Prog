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
int a[MAXN], b[MAXN];
vector<pii> up, down;

bool Comp(const pii& a, const pii& b)
{
    return pii(a.SS, a.FF) < pii(b.SS, b.FF);
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

    sort(up.begin(), up.end());
    sort(down.begin(), down.end(), Comp);

    multiset<pii> itvs;
    for (int i = 0; i < down.size(); i++) itvs.insert(down[i]);

    int id = 0;
    for (int i = 0; i < up.size(); i++)
    {
        while (id < down.size() && down[id].SS < up[i].SS) 
            itvs.erase(itvs.find(down[id++]));
        
        if (!itvs.empty())
            inc = max(inc, (ll) (up[i].SS - max(itvs.begin()->FF, up[i].FF)));
    }

    sort(up.begin(), up.end(), Comp);
    sort(down.begin(), down.end());

    itvs.clear();
    for (int i = 0; i < up.size(); i++) itvs.insert(up[i]);

    id = 0;
    for (int i = 0; i < down.size(); i++)
    {
        while (id < up.size() && up[id].SS < down[i].SS) 
            itvs.erase(itvs.find(up[id++]));
        
        if (!itvs.empty())
            inc = max(inc, (ll) (down[i].SS - max(itvs.begin()->FF, down[i].FF)));
    }

    cout << ans - inc * 2 << endl;
    return 0;
}