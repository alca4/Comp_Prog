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
vector<int> nbs[MAXN];
pii dp[MAXN][2];
vector<pii> nextv[MAXN][2];
int chosen[MAXN];

bool better(pii p1, pii p2)
{
    return p1.FF == p2.FF ? p1.SS < p2.SS : p1.FF > p2.FF;
}

void DP(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) DP(nbs[a][i], a);

    // calculate 0
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        pii best;
        if (better(dp[nbs[a][i]][0], dp[nbs[a][i]][1]))
        {
            best = dp[nbs[a][i]][0];
            nextv[a][0].pb({nbs[a][i], 0});
        }
        else
        {
            best = dp[nbs[a][i]][1];
            nextv[a][0].pb({nbs[a][i], 1});
        }
        dp[a][0].FF += best.FF;
        dp[a][0].SS += best.SS;
    }
    dp[a][0].SS++;

    // calculate 1
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        nextv[a][1].pb({nbs[a][i], 0});
        dp[a][1].FF += dp[nbs[a][i]][0].FF;
        dp[a][1].SS += dp[nbs[a][i]][0].SS;
    }
    dp[a][1].FF++;
    dp[a][1].SS += nbs[a].size();
}

void Deconstruct(int a, int b)
{
    chosen[a] = b;
    for (int i = 0; i < nextv[a][b].size(); i++) 
        Deconstruct(nextv[a][b][i].FF, nextv[a][b][i].SS);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    if (N == 2)
    {
        cout << "2 2" << endl;
        cout << "1 1" << endl;
        return 0;
    }

    DP(1, 0);
    pii best = better(dp[1][0], dp[1][1]) ? dp[1][0] : dp[1][1];
    cout << best.FF << " " << best.SS << endl;

    if (better(dp[1][0], dp[1][1])) Deconstruct(1, 0);
    else Deconstruct(1, 1);

    for (int i = 1; i <= N; i++) 
    {
        if (chosen[i] == 0) cout << 1 << " ";
        else cout << nbs[i].size() << " ";
    }
    return 0;
} 