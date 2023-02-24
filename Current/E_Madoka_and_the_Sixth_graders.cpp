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
int ans[MAXN], nextv[MAXN], arr[MAXN];
int nbs[MAXN][32];
set<int> options[MAXN];
int nnb[MAXN];

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
        cin >> nextv[i];
        vals.insert(nextv[i]);
    }
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        maxval = max(maxval, arr[i]);
    }
    repvals = N - vals.size();
    T = (maxval - N) / repvals;

    for (int i = 1; i <= N; i++) nbs[i][0] = nextv[i];
    
    for (int i = 1; i <= N; i++)
        for (int j = 1; j < 32; j++) nbs[i][j] = nbs[nbs[i][j - 1]][j - 1];
    
    for (int i = 1; i <= N; i++)
    {
        int x = i;
        for (int j = 0; j < 32; j++) if (T & (1 << j)) x = nbs[x][j];
        options[arr[x]].insert(i);
        nnb[i] = x;
    }

    vals.clear();
    for (int i = 1; i <= N; i++) vals.insert(i);
    for (int i = 1; i <= N; i++) if (arr[i] <= N) vals.erase(arr[i]);

    for (int i = 1; i <= N; i++)
    {
        int v = arr[nnb[i]];
        cout << i << " ";
        if (v > N || !options[v].size())
        {
            cout << 1 << endl;
            ans[i] = *vals.begin();
            vals.erase(vals.begin());
        }
        else if (options[v].size() > 1 && v > *vals.begin())
        {
            cout << 2 << endl;
            ans[i] = *vals.begin();
            options[v].erase(i);
            vals.erase(vals.begin());
        }
        else
        {
            cout << 3 << endl;
            ans[i] = v;
            options[v].clear();
        }
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;
    
    return 0;
} 