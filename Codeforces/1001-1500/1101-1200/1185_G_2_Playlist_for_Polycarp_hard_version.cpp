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

const int MAXN = 60;
int N, T, C[4];
ll fact[MAXN];
pll songs[MAXN];
vector<vector<pll>> dp[MAXN * MAXN];
vector<pll> dp2[MAXN * MAXN];
ll combos[MAXN][MAXN][MAXN][4];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> T;
    fact[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        int a, b;
        cin >> a >> b;
        songs[i] = {a, b};
        C[b]++;
        fact[i] = mult(i, fact[i - 1]);
    }

    bool s1 = 0;
    if (C[1] > C[3]) 
    {
        s1 = 1;
        swap(C[1], C[3]);
        for (int i = 1; i <= N; i++)
        {
            if (songs[i].SS == 1) songs[i].SS = 3;
            else if (songs[i].SS == 3) songs[i].SS = 1;
        }
    }

    if (C[2] > C[3])
    {
        swap(C[2], C[3]);
        for (int i = 1; i <= N; i++)
        {
            if (songs[i].SS == 3) songs[i].SS = 2;
            else if (songs[i].SS == 2) songs[i].SS = 3;
        }
    }

    combos[1][1][0][1] = combos[1][0][1][2] = combos[1][0][0][3] = 1;
    for (int i = 2; i <= N; i++) for (int j = 0; j <= C[1]; j++) 
        for (int k = 0; k <= C[2]; k++) 
    {
        if (i - j - k > C[3]) continue;
        if (j > 0)
            combos[i][j][k][1] += combos[i - 1][j - 1][k][2] + combos[i - 1][j - 1][k][3];
        if (k > 0)
            combos[i][j][k][2] += combos[i - 1][j][k - 1][1] + combos[i - 1][j][k - 1][3];
        if (i - j - k > 0)
            combos[i][j][k][3] += combos[i - 1][j][k][1] + combos[i - 1][j][k][2];
        
        while (combos[i][j][k][1] >= MOD) combos[i][j][k][1] -= MOD;
        while (combos[i][j][k][2] >= MOD) combos[i][j][k][2] -= MOD;
        while (combos[i][j][k][3] >= MOD) combos[i][j][k][3] -= MOD;
    }

    // cout << combos[N][1][0][1] + combos[N][1][0][2] + combos[N][1][0][3] << endl;

    ll ans = 0;
    for (int k = 0; k <= T; k++)
    {
        dp[k].resize(C[1] + 1);
        for (int h = 0; h <= C[1]; h++) dp[k][h].resize(C[2] + 1);
    }
    dp[0][0][0].FF = 1;
    for (int j = 1; j <= N; j++)
    {
        for (int l = 0; l <= C[1]; l++) for (int m = 0; m <= C[2]; m++)
            for (int k = 0; k <= T; k++) 
            {
                if (songs[j].SS == 1 && l > 0 && k >= songs[j].FF)
                    dp[k][l][m].SS += dp[k - songs[j].FF][l - 1][m].FF;
                if (songs[j].SS == 2 && m > 0 && k >= songs[j].FF)
                    dp[k][l][m].SS += dp[k - songs[j].FF][l][m - 1].FF;
                dp[k][l][m].SS += dp[k][l][m].FF;
                while (dp[k][l][m].SS >= MOD) dp[k][l][m].SS -= MOD;
            }   
        for (int l = 0; l <= C[1]; l++) for (int m = 0; m <= C[2]; m++)
            for (int k = 0; k <= T; k++) dp[k][l][m].FF = dp[k][l][m].SS, dp[k][l][m].SS = 0;
        // cout << dp[0][0][0].FF << endl;
    }

    for (int k = 0; k <= T; k++) 
        dp2[k].resize(C[3] + 1);
    dp2[0][0].FF = 1;
    for (int j = 1; j <= N; j++) 
    {
        for (int k = 0; k <= T; k++) for (int l = 0; l <= C[3]; l++)
        {
            if (songs[j].SS == 3 && l > 0 && k >= songs[j].FF)
                dp2[k][l].SS += dp2[k - songs[j].FF][l - 1].FF;
            
            dp2[k][l].SS += dp2[k][l].FF;
            while (dp2[k][l].SS >= MOD) dp2[k][l].SS -= MOD;
        }
        for (int k = 0; k <= T; k++) for (int l = 0; l <= C[3]; l++) 
            dp2[k][l].FF = dp2[k][l].SS, dp2[k][l].SS = 0;
    }
    
    for (int j = 0; j <= T; j++) for (int k = 0; k <= C[1]; k++) 
        for (int l = 0; l <= C[2]; l++) for (int m = 0; m <= C[3]; m++)
        {
            ll s = (combos[k + l + m][k][l][1] + 
                    combos[k + l + m][k][l][2] + 
                    combos[k + l + m][k][l][3]);
            while (s >= MOD) s -= MOD;
            ans += mult(mult(s, mult(fact[k], mult(fact[l], fact[m]))),
                        mult(dp[j][k][l].FF, dp2[T - j][m].FF));
            if (ans >= MOD) ans -= MOD;
            // cout << ans << " " << j << " " << k << " " << l << " " << m << endl;
        }

    cout << ans << endl;
    return 0;
} 