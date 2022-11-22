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
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
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

const int MAXN = 300010;
int N, Q;

struct Query
{
    int l, r, id;
};
int ans[MAXN];

pii arr[MAXN];
map<int, int> pts;

struct Itv
{
    ll l, r, w;
};
set<Itv> ranges;

ll calc(int a, int b, int wa, int wb)
{
    return abs(a - b) * (wa + wb);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i].FF >> arr[i].SS;
    sort(arr + 1, arr + 1 + N);

    for (int i = 1; i <= N; i++)
    {
        auto it = pts.upper_bound(arr[i].SS);
        if (it != pts.begin()) 
        {
            --it;
            ranges.insert({it->SS, arr[i].FF, calc(it->SS, arr[i].SS)});
        }
    }
} 