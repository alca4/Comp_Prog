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
int N, M, T;
int ans[MAXN], arr[MAXN];
int nbs[MAXN][32];
set<int> options[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    set<int> vals;
    int repvals = 0, maxval = 0;
    for (int i = 1; i <= N; i++) 
    {
        cin >> nbs[i][0];
        vals.insert(nbs[i][0]);
    }
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        maxval = max(maxval, arr[i]);
    }
    repvals = N - vals.size();
    T = (maxval - N) / repvals;
    
    for (int j = 1; j < 32; j++) for (int i = 1; i <= N; i++)
        nbs[i][j] = nbs[nbs[i][j - 1]][j - 1];
    
    for (int i = 1; i <= N; i++)
    {
        int x = i;
        for (int j = 0; j < 32; j++) if (T & (1 << j)) x = nbs[x][j];
        options[arr[x]].insert(i);
        // cout << T << "th neighbor of " << i << " is " << x << endl;
    }

    vals.clear();

    for (int i = 1; i <= N; i++)
    {
        if (options[i].size())
        {
            // cout << "min element put at " << *options[i].begin() << endl;
            ans[*options[i].begin()] = i;
            for (auto n : options[i]) if (n != *options[i].begin())
                vals.insert(n);
        }
        else
        {
            if (!vals.size()) break;
            // cout << "best element put at " << *vals.begin() << endl;
            ans[*vals.begin()] = i;
            vals.erase(vals.begin());
        }
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;
    
    return 0;
} 