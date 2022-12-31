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

const int MAXN = 510, MAXM = 10010;
int N, C;
struct App
{
    int d, s, id;
} apps[MAXN];
int dp[MAXN][MAXM];
pii p[MAXN][MAXM];

bool operator<(const App& p1, const App& p2)
{
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> C;
    for (int i = 1; i <= N; i++) 
    {
        cin >> apps[i].d >> apps[i].s;
        apps[i].id = i;
    }

    sort(apps + 1, apps + 1 + N);

    dp[0][C] = 1;
    for (int i = 1; i <= N; i++)
    {
        for (int j = max(0, apps[i].d - apps[i].s); j <= C - apps[i].s; j++)
        {
            if (dp[i - 1][j + apps[i].s])
            {
                if (dp[i - 1][j + apps[i].s] + 1 > dp[i][j])
                {
                    dp[i][j] = dp[i - 1][j + apps[i].s] + 1;
                    p[i][j] = {i - 1, j + apps[i].s};
                }
            }
        }
        for (int j = 0; j <= C; j++)
        {
            if (dp[i - 1][j] > dp[i][j])
            {
                dp[i][j] = dp[i - 1][j];
                p[i][j] = {i - 1, j};
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= C; i++) if (dp[N][i] > dp[N][ans]) ans = i;
    
    vector<int> points;
    int i = N, j = ans;
    while (i != 0 && j != C)
    {
        if (j != p[i][j].SS) points.pb(apps[i].id);
        pii tmp = p[i][j];
        i = tmp.FF;
        j = tmp.SS;
    }

    reverse(points.begin(), points.end());
    
    cout << points.size() << endl;
    for (int i = 0; i < points.size(); i++) cout << points[i] << " ";
    if (points.size() != 0) cout << endl;
    return 0;
} 