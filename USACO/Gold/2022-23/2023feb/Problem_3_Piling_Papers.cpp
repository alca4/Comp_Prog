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

const int MAXN = 301, MD = 18;
int N, M[2], Q;
int NM[MD][2];
int digs[MAXN];
ll dp[2][MAXN][MD][MD][3];
struct Query {int l, r, id, ans;};
vector<Query> queries;

bool operator<(const Query& q1, const Query& q2)
{
    return pii(q1.l, q1.r) < pii(q2.l, q2.r);
}

bool Comp(const Query& q1, const Query& q2)
{
    return q1.id < q2.id;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll a, b;
    cin >> N >> a >> b;
    M[0] = log10(a);
    for (int i = 0; i < MD; i++) 
    {
        NM[i][0] = a % 10;
        a /= 10;
    }
    M[1] = log10(b);
    for (int i = 0; i < MD; i++) 
    {
        NM[i][1] = b % 10;
        b /= 10;
    }
    for (int i = 1; i <= N; i++) cin >> digs[i];

    cin >> Q;
    for (int i = 1; i <= Q; i++)
    {
        int l, r;
        cin >> l >> r;
        queries.pb({l, r, i});
    }
    sort(queries.begin(), queries.end());

    int x = 0;
    for (int s = 1; s <= N; s++) 
    {
        for (int i = s; i <= N; i++) for (int t = 0; t <= 1; t++)
        for (int l = 0; l <= M[t]; l++) for (int r = l; r <= M[t]; r++) 
        {
            dp[t][i][l][r][0] += dp[t][i - 1][l][r][0];
            dp[t][i][l][r][1] += dp[t][i - 1][l][r][1];
            dp[t][i][l][r][2] += dp[t][i - 1][l][r][2];

            if (digs[i] < NM[l][t]) 
            {
                if (l == r) dp[t][i][l][r][0]++;
                else 
                {
                    dp[t][i][l][r][0] += dp[t][i - 1][l + 1][r][0];
                    dp[t][i][l][r][0] += dp[t][i - 1][l + 1][r][1];
                    dp[t][i][l][r][2] += dp[t][i - 1][l + 1][r][2];
                }
            }
            if (digs[i] == NM[l][t]) 
            {
                if (l == r) dp[t][i][l][r][1]++;
                else 
                {
                    dp[t][i][l][r][0] += dp[t][i - 1][l + 1][r][0];
                    dp[t][i][l][r][1] += dp[t][i - 1][l + 1][r][1];
                    dp[t][i][l][r][2] += dp[t][i - 1][l + 1][r][2];
                }
            }
            if (digs[i] > NM[l][t]) 
            {
                if (l == r) dp[t][i][l][r][2]++;
                else 
                {
                    dp[t][i][l][r][0] += dp[t][i - 1][l + 1][r][0];
                    dp[t][i][l][r][2] += dp[t][i - 1][l + 1][r][1];
                    dp[t][i][l][r][2] += dp[t][i - 1][l + 1][r][2];
                }
            }

            if (digs[i] < NM[r][t]) 
            {
                if (l == r) dp[t][i][l][r][0]++;
                else 
                {
                    dp[t][i][l][r][0] += dp[t][i - 1][l][r - 1][0];
                    dp[t][i][l][r][0] += dp[t][i - 1][l][r - 1][1];
                    dp[t][i][l][r][0] += dp[t][i - 1][l][r - 1][2];
                }
            }
            if (digs[i] == NM[r][t]) 
            {
                if (l == r) dp[t][i][l][r][1]++;
                else 
                {
                    dp[t][i][l][r][0] += dp[t][i - 1][l][r - 1][0];
                    dp[t][i][l][r][1] += dp[t][i - 1][l][r - 1][1];
                    dp[t][i][l][r][2] += dp[t][i - 1][l][r - 1][2];
                }
            }
            if (digs[i] > NM[r][t]) 
            {
                if (l == r) dp[t][i][l][r][2]++;
                else 
                {
                    dp[t][i][l][r][2] += dp[t][i - 1][l][r - 1][0];
                    dp[t][i][l][r][2] += dp[t][i - 1][l][r - 1][1];
                    dp[t][i][l][r][2] += dp[t][i - 1][l][r - 1][2];
                }
            }

            while (dp[t][i][l][r][0] >= MOD) dp[t][i][l][r][0] -= MOD;
            while (dp[t][i][l][r][1] >= MOD) dp[t][i][l][r][1] -= MOD;
            while (dp[t][i][l][r][2] >= MOD) dp[t][i][l][r][2] -= MOD;
        }

        while (queries[x].l == s)
        {
            int r = queries[x].r;
            ll a1 = dp[1][r][0][M[1]][1] + dp[1][r][0][M[1]][0];
            // cout << a1 << endl;
            for (int i = 1; i <= M[1]; i++)
            {
                a1 += dp[1][r][i][M[1]][0] + dp[1][r][i][M[1]][1] + dp[1][r][i][M[1]][2];
                // cout << "i1 is: " << dp[1][r][i][M[1]][0] + dp[1][r][i][M[1]][1] + dp[1][r][i][M[1]][2] << endl;
            }
            
            while (a1 >= MOD) a1 -= MOD;

            ll a2 = dp[0][r][0][M[0]][0];
            // cout << a2 << endl;
            for (int i = 1; i <= M[0]; i++)
            {
                a2 += dp[0][r][i][M[0]][0] + dp[0][r][i][M[0]][1] + dp[0][r][i][M[0]][2];
                // cout << "i2 is: " << dp[0][r][i][M[0]][0] + dp[0][r][i][M[0]][1] + dp[0][r][i][M[0]][2] << endl;
            }
            
            while (a2 >= MOD) a2 -= MOD;

            // cout << a1 << " " << a2 << endl;

            ll ans = (a1 - a2 + MOD);
            if (ans >= MOD) ans -= MOD;

            queries[x].ans = ans;
            x++;
        }

        for (int i = s; i <= N; i++) for (int t = 0; t <= 1; t++)
        for (int l = 0; l <= M[t]; l++) for (int r = l; r <= M[t]; r++) for (int n = 0; n <= 2; n++)
            dp[t][i][l][r][n] = 0;
    }

    sort(queries.begin(), queries.end(), Comp);
    
    for (int i = 0; i < queries.size(); i++) cout << queries[i].ans << "\n";
    return 0;
} 