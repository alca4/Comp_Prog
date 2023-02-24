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

const int MAXN = 90;
int N;
struct Point 
{
    int x, y, id;
} pts[MAXN];
bool operator<(const Point& p1, const Point& p2) {return pii(p1.x, p1.y) < pii(p2.x, p2.y);}
ll dp[MAXN][MAXN][MAXN][2];
int lines[MAXN][MAXN];
int triangles[MAXN][MAXN][MAXN];

int sign(ll a) {return (a > 0) - (a < 0);}
ll cp(pii p1, pii p2) {return 1ll * p1.FF * p2.SS - 1ll * p1.SS * p2.FF;}
int orientation(pii p1, pii p2, pii p3) 
{
    return sign(cp(pii(p2.FF - p1.FF, p2.SS - p1.SS), pii(p3.FF - p2.FF, p3.SS - p2.SS)));
}
int dist(const pii& p1, const pii& p2)
{
    return (p1.FF - p2.FF) * (p1.FF - p2.FF) + (p1.SS - p2.SS) * (p1.SS - p2.SS);
}

void find_interior_points()
{
    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) 
    {
        int ans = 0;
        for (int k = 1; k <= N; k++) 
        {
            if (pts[k].x >= pts[j].x && pts[k].x <= pts[i].x &&
                orientation({pts[i].x, pts[i].y}, {pts[k].x, pts[k].y}, {pts[j].x, pts[j].y}) < 0)
                ans++;
        }
        lines[pts[i].id][pts[j].id] = lines[pts[j].id][pts[i].id] = ans;
    }

    for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) for (int k = 1; k < j; k++)
    {
        int x;
        if (orientation({pts[i].x, pts[i].y}, {pts[j].x, pts[j].y}, {pts[k].x, pts[k].y}) > 0)
        {
            x = lines[pts[i].id][pts[j].id] + lines[pts[j].id][pts[k].id] - lines[pts[i].id][pts[k].id];
            if (pts[j - 1].x == pts[j].x) x--;
        }
        else
        {
            x = lines[pts[i].id][pts[k].id] - lines[pts[i].id][pts[j].id] - lines[pts[j].id][pts[k].id] - 1;
            if (pts[j - 1].x == pts[j].x) x++;
        }

        vector<int> tmp = {pts[i].id, pts[j].id, pts[k].id};
        sort(tmp.begin(), tmp.end());
        triangles[tmp[0]][tmp[1]][tmp[2]] = x;
    }
}

int s;
ll pow2[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> pts[i].x >> pts[i].y;
        pts[i].id = i;
    }

    pow2[0] = 1;
    for (int i = 1; i <= N; i++) pow2[i] = mult(pow2[i - 1], 2);

    sort(pts + 1, pts + 1 + N);

    find_interior_points();

    ll ans = 0;

    for (s = 1; s <= N; s++)
    {
        sort(pts + s + 1, pts + 1 + N, [](const Point& a, const Point& b)
        {
            ll dy1 = a.y - pts[s].y;
            ll dx1 = a.x - pts[s].x;
            ll dy2 = b.y - pts[s].y;
            ll dx2 = b.x - pts[s].x;
            return dy1 * dx2 < dy2 * dx1;
        });

        for (int k = s + 1; k <= N; k++) for (int j = s + 1; j < k; j++)
        {
            // if (orientation({pts[s].x, pts[s].y}, {pts[j].x, pts[j].y}, {pts[k].x, pts[k].y}) < 0) continue;
            ll p = abs(0ll + pts[s].x * pts[j].y - pts[s].y * pts[j].x + 
                              pts[j].x * pts[k].y - pts[j].y * pts[k].x +
                              pts[k].x * pts[s].y - pts[k].y * pts[s].x) % 2;
            
            vector<int> tmp = {pts[s].id, pts[j].id, pts[k].id};
            sort(tmp.begin(), tmp.end());
            dp[k + 1][j][k][p] = pow2[triangles[tmp[0]][tmp[1]][tmp[2]]];
        }

        for (int i = s + 2; i <= N; i++) for (int k = s + 1; k < i; k++)
        for (int j = s + 1; j < k; j++) 
        {
            dp[i + 1][j][k][0] += dp[i][j][k][0];
            dp[i + 1][j][k][1] += dp[i][j][k][1];

            if (dp[i + 1][j][k][0] >= MOD) dp[i + 1][j][k][0] -= MOD;
            if (dp[i + 1][j][k][1] >= MOD) dp[i + 1][j][k][1] -= MOD;

            if (orientation({pts[j].x, pts[j].y}, {pts[k].x, pts[k].y}, {pts[i].x, pts[i].y}) < 0) continue;

            ll p = abs(0ll + pts[s].x * pts[i].y - pts[s].y * pts[i].x + 
                              pts[i].x * pts[k].y - pts[i].y * pts[k].x +
                              pts[k].x * pts[s].y - pts[k].y * pts[s].x) % 2;

            vector<int> tmp = {pts[i].id, pts[s].id, pts[k].id};
            sort(tmp.begin(), tmp.end());

            dp[i + 1][k][i][0] += mult(dp[i][j][k][p], pow2[triangles[tmp[0]][tmp[1]][tmp[2]]]);
            dp[i + 1][k][i][1] += mult(dp[i][j][k][1 - p], pow2[triangles[tmp[0]][tmp[1]][tmp[2]]]);

            if (dp[i + 1][k][i][1] >= MOD) dp[i + 1][k][i][1] -= MOD;
            if (dp[i + 1][k][i][0] >= MOD) dp[i + 1][k][i][0] -= MOD;
        }

        for (int k = s + 1; k <= N; k++) for (int j = s + 1; j < k; j++) 
        {
            ans += dp[N + 1][j][k][0];
            if (ans >= MOD) ans -= MOD;
        }

        for (int i = 1; i <= N + 1; i++) for (int j = 1; j <= N; j++) for (int k = 1; k <= N; k++)
            dp[i][j][k][0] = dp[i][j][k][1] = 0;

        sort(pts + 1, pts + 1 + N);
    }

    cout << ans << endl;
    return 0;
}