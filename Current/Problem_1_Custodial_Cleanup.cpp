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
#define endl "\n"
ll INF = INT_MAX;
ll LINF = LONG_MAX;
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

const int MAXN = 9;
int N, M;
int dp[20010][(1 << MAXN)];
vector<int> nbs[MAXN];
int f[MAXN], c[MAXN], s[MAXN];
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

int at(int x, int m)
{
    while (x--) m /= 3;
    return m % 3;
}

void solve()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> c[i];
    for (int i = 0; i < N; i++) cin >> s[i];
    for (int i = 0; i < N; i++) cin >> f[i];
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    dp[1][1] = 1;
    for (int mask = 0; mask < power(3, N); mask++) 
        for (int keys = 0; keys < (1 << N); keys++) 
    {
        if (!dp[mask][keys]) continue;

        cout << mask << " " << keys << endl;

        for (int j = 0; j < N; j++) if (at(j, mask) == 1)
        {
            for (int nb : nbs[j]) 
            {
                int clearance = 0;
                for (int k = 0; k < N; k++) if ((keys & (1 << k)) && s[k] == c[nb]) 
                    clearance = 1;
                
                if (clearance && (at(nb, mask) == 0)) 
                    dp[mask + power(3, nb)][keys | (1 << nb)] = 1;

                bool good = 0;
                map<int, vector<int>> colors;
                for (int k = 0; k < N; k++) if (at(k, mask) == 1)
                {
                    if (k == 0 || colors.size() > 1) good = 1;
                    colors[c[k]].pb(-1);
                }

                for (int k = 0; k < N; k++) if ((keys & (1 << k)) && colors.count(s[k]))
                    colors[s[k]].pb(k);
                
                for (auto n : colors)
                {
                    for (auto nb : n.SS) 
                        if ((n.SS.size() > 1 || n.FF == c[0]) && nb != -1)
                        {
                            cout << nb << endl;
                            dp[mask + power(3, j)][keys & !(1 << nb)] = 1;
                            cout << "maybe to " << mask + power(3, j) << " " << (keys & !(1 << nb)) << endl;
                            // cout << dp[5][1] << endl;
                        }
                }
            }
        }
    }

    int ans = 1;

    for (int i = 0; i < N; i++) if (s[i] == f[i])
    {
        for (int j = 0; j < power(3, N); j++) 
        {
            if (at(i, j) == 1)
                for (int k = 0; k < (1 << N); k++)
                    dp[j + power(3, i)][k] |= dp[j][k];
            
            if (at(i, j) == 0)
                for (int k = 0; k < (1 << N); k++)
                    dp[j + 2 * power(3, i)][k] |= dp[j][k];
        }
    }

    if (dp[power(3, N) - 2][1]) cout << "YES" << endl;
    else cout << "NO" << endl;

    for (int i = 0; i < power(3, N); i++) for (int j = 0; j < (1 << N); j++)
        dp[i][j] = 0;
    
    for (int i = 1; i <= N; i++)
    {
        c[i] = f[i] = s[i] = 0;
        nbs[i].clear();
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