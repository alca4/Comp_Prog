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
ll MOD = LINF;
// ll MOD = 1000000007;
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

const int MAXN = 1010;
int N, M;
vector<int> nbs[MAXN];
int p[MAXN], np[MAXN];
int dp[MAXN][MAXN];
int relevant[MAXN];
int depth[MAXN];
// ll fact[MAXN], factinv[MAXN];

// ll choose(int a, int b)
// {
//     return mult(fact[a], mult(factinv[b], factinv[a - b]));
// }

// void get_fact(int x)
// {
//     fact[0] = 1;
//     for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
//     factinv[x] = divide(1, fact[x]);
//     for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
// }

void DP(int a)
{
    for (int nb : nbs[a])
    {
        depth[nb] = depth[a] + 1;
        DP(nb);
    }
}

void DP2(int a, set<int>& ans)
{
    set<int> ids;
    for (int i = 1; i <= N; i++) if (depth[i] == depth[a]) ids.insert(i);
    for (int nb : nbs[a]) 
    {
        set<int> tmp;
        DP2(nb, tmp);
        
        vector<int> del;
        for (int d : ids) if (!tmp.count(d)) del.pb(d);
        for (int d : del) ids.erase(d);
    }
    
    if (!relevant[a])
    {
        for (int nb : ids)
        {
            if (nb > a && relevant[nb]) 
            {
                dp[a][nb] = 1;
                ans.insert(np[nb]);
            }
        }
    }
    else 
    {
        ans.insert(np[a]);
    }
}

void DP3(int a)
{
    for (int nb : nbs[a]) if (!relevant[nb])
    {
        for (int nb2 : nbs[a]) if (dp[nb][nb2] && nb2 != nb)  
        {
            cout << nb << " " << nb2 << endl;
            for (int nb3 : nbs[nb]) nbs[nb2].pb(nb3);
            break;
        }
    }

    for (int nb : nbs[a]) if (relevant[nb]) DP3(nb);
}

void solve()
{
    cin >> N;
    set<int> root;
    for (int i = 1; i <= N; i++) root.insert(i);
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[b].pb(a);
        root.erase(a);
        p[a] = b;
    }

    cin >> M;
    for (int i = 1; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        np[a] = b;
        relevant[a] = 1;
        relevant[b] = 1;
    }

    int r = *root.begin();
    DP(r);
    set<int> tmp;
    DP2(r, tmp);
    cout << N - M << endl;
    DP3(r);

    for (int i = 1; i <= N; i++) 
    {
        nbs[i].clear();
        np[i] = p[i] = depth[i] = relevant[i] = 0;
        for (int j = 1; j <= N; j++) dp[i][j] = 0;
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
    while (T--) solve();

    return 0;
} 