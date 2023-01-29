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

ll add(const ll a, const ll b) {return (a + b) % MOD;}
ll sub(const ll a, const ll b) {return (a + MOD - b) % MOD;}
ll mult(const ll a, const ll b) {return (a * b) % MOD;}
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
ll divide(const ll a, const ll b) {return (a * power(b, MOD - 2)) % MOD;}
void maxeq(auto& a, const auto b) {a = max(a, b);}
void mineq(auto& a, const auto b) {a = min(a, b);}

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

const int MAXN = 2010;
int N, A, B;
struct Friend
{
    int p, c, x;
} fwends[MAXN];
int dpf[MAXN][MAXN];
int dpb[MAXN][MAXN];

bool operator<(const Friend& f1, const Friend& f2)
{
    return f1.x < f2.x;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) cin >> fwends[i].p >> fwends[i].c >> fwends[i].x;

    sort(fwends + 1, fwends + N + 1);

    for (int i = 0; i <= A; i++) dpb[N + 1][i] = 1;
    for (int i = N; i >= 1; i--)
    {
        for (int j = 0; j <= 2000; j++)
        {
            maxeq(dpb[i][j], dpb[i + 1][j]);
            if (j >= fwends[i].c) 
                maxeq(dpb[i][j], dpb[i + 1][j - fwends[i].c] + fwends[i].p);
        }
    }

    // for (int i = 0; i <= A; i++)
    // {
    //     for (int j = 1; j <= N; j++) cout << dpb[j][i] - 1 << " ";
    //     cout << endl;
    // }

    int ans = 0;
    for (int i = 0; i <= B; i++) dpf[0][i] = 1;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= 2000; j++)
        {
            if (!dpf[i][j]) continue;
            maxeq(dpf[i + 1][j], dpf[i][j]);
            if (j > fwends[i + 1].c * fwends[i + 1].x)
                maxeq(dpf[i + 1][j - fwends[i + 1].c * fwends[i + 1].x], dpf[i][j] + fwends[i + 1].p);
            else
            {
                // cout << "considering " << i + 1 << " with " << j << endl;
                int dc = j / fwends[i + 1].x;
                if (A < fwends[i + 1].c - dc) continue;
                int a = dpb[i + 2][A - (fwends[i + 1].c - dc)];
                if (a) a--;
                maxeq(ans, dpf[i][j] - 1 + fwends[i + 1].p + a);
            }
        }
    }

    cout << ans << endl;
    return 0;
} 