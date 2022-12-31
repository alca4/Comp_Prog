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

const int MAXN = 200010;
int N;
ll arr[MAXN];
ll rev[MAXN];
ll fact[MAXN];
ll factinv[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    fact[0] = factinv[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = (fact[i - 1] * N) % MOD; 
    for (int i = 1; i <= N; i++) factinv[i] = divide(factinv[i - 1], N);
    
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) arr[i]--;
    for (int i = 1; i <= N; i++) rev[i] = arr[i];

    for (int i = 1; i <= N; i++) arr[i] = add(arr[i - 1], mult(arr[i], fact[i]));
    for (int i = N; i >= 1; i--) rev[i] = add(rev[i + 1], mult(rev[i], fact[N - i + 1]));

    map<int, vector<int>> best;
    for (int k = 1; k <= N; k++)
    {
        set<ll> vals;
        for (int i = 0; i + k <= N; i += k)
        {
            ll v1 = mult(factinv[i], sub(arr[i + k], arr[i]));
            ll v2 = mult(factinv[N - i - k], sub(rev[i + 1], rev[i + k + 1]));
            
            ll ans = min(v1, v2);
            if (!vals.count(ans)) vals.insert(ans);
        }

        best[vals.size()].pb(k);
    }

    auto tmp = --best.end();
    cout << tmp->FF << " " << tmp->SS.size() << endl;
    for (int i = 0; i < tmp->SS.size(); i++) cout << tmp->SS[i] << " ";
    cout << endl;

    return 0;
} 