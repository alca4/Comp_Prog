/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
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
#define ull unsigned ll
#define endl "\n"
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

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
int N, M, D;
vector<int> nbs[60 * MAXN];
bitset<60 * MAXN> vis;
bitset<60 * MAXN> zs;
int arr[MAXN];

void DFS(int a)
{
    if (vis[a]) return;
    vis[a] = 1;
    for (int nb : nbs[a]) DFS(nb);
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    D = 30 * N;
    for (int j = 1; j <= M; j++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        for (int i = 0; i < 30; i++) 
        {
            if (a == b)
            {
                int x = (c & (1 << i)) > 0;
                zs[a * 30 + i + x * D] = 1;
            }
            else if (c & (1 << i)) 
            {
                nbs[a * 30 + i].pb((b * 30 + i) + D);
                nbs[b * 30 + i].pb((a * 30 + i) + D);
            }
            else
            {
                zs[a * 30 + i] = 1;
                zs[b * 30 + i] = 1;
            }
        }
    }

    for (int i = 0; i < 60 * N; i++) if (zs[i]) DFS(i);

    for (int i = 0; i < N; i++)
    {
        for (int j = 29; j >= 0; j--) 
        {
            if (vis[i * 30 + j + D]) arr[i] += (1 << j);
            else if (!vis[i * 30 + j])
                DFS(i * 30 + j);
        }
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
} 