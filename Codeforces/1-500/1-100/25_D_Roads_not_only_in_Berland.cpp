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
ll MOD = 1000000007;

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

const int MAXN = 1010;
int N;

int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

vector<pii> close;
vector<pii> open;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;

    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        if (!combine(a, b)) close.pb({a, b});
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        if (combine(i, j)) open.pb({i, j});

    cout << close.size() << endl;
    for (int i = 0; i < close.size(); i++)
        cout << close[i].FF << " " << close[i].SS << " " << open[i].FF << " " << open[i].SS << endl;
    return 0;
} 