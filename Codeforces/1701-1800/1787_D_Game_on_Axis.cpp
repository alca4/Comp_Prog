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
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}

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
int nextv[MAXN], c[MAXN], vis[MAXN], flow[MAXN], is_root[MAXN], nab[MAXN];
vector<int> prevv[MAXN];
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[N]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

bool in_range(int a) {return 1 <= a && a <= N;}

void traverse(int a)
{
    vis[a] = 1;
    int nb = a + nextv[a];
    if (in_range(nb)) 
    {
        if (vis[nb]) 
        {
            if (c[nb] != c[a]) flow[a] = flow[nb];
        }
        else 
        {
            c[nb] = c[a];
            traverse(nb);
            c[a] = c[nb];
            flow[a] = flow[nb];
        }
    }
    else 
    {
        flow[a] = 1;
        is_root[a] = 1;
    }
}

void DFS(int a)
{
    nab[a] = 1;
    for (int nb : prevv[a]) 
    {
        DFS(nb);
        nab[a] += nab[nb];
    }
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N;
        for (int i = 1; i <= N; i++) 
        {
            cin >> nextv[i];
            if (in_range(i + nextv[i])) prevv[i + nextv[i]].pb(i);
        }

        for (int i = 1; i <= N; i++) if (!vis[i]) 
        {
            // cout << "trying " << i << endl;
            c[i] = i;
            traverse(i);
        }

        // for (int i = 1; i <= N; i++) cout << c[i] << " ";
        // cout << endl;
        // for (int i = 1; i <= N; i++) cout << flow[i] << " ";
        // cout << endl;

        int closed = 0;
        for (int i = 1; i <= N; i++) if (!flow[i]) closed++;

        for (int i = 1; i <= N; i++) if (is_root[i] && flow[i]) 
            DFS(i);

        // for (int i = 1; i <= N; i++) cout << nab[i] << " ";
        // cout << endl;

        ll ans = 0;
        for (int i = 1; i <= N; i++)
        {
            ans += 2 * N + 1;
            if (c[i] == 1)
            {
                ans -= closed;
                if (flow[i]) ans -= nab[i];
            }
            else if (!flow[1]) ans -= 2 * N + 1;
        }

        cout << ans << endl;

        for (int i = 1; i <= N; i++) 
        {
            nextv[i] = c[i] = vis[i] = flow[i] = nab[i] = is_root[i] = 0;
            prevv[i].clear();
        }
    }

    return 0;
} 