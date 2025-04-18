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

const int MAXN = 3010;
int N, M;
vector<int> nbs[MAXN];
int df[MAXN][MAXN];
int vis[MAXN];
vector<pii> d1[MAXN], d2[MAXN];
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

void BFS(int a)
{
    vis[a] = 1;
    queue<pii> search;
    search.push(pii(a, 0));
    while (!search.empty())
    {
        int n = search.front().FF;
        int d = search.front().SS;
        search.pop();

        for (int nb : nbs[n]) 
        {
            if (!vis[nb])
            {
                df[a][nb] = d + 1;
                vis[nb] = 1;
                search.push(pii(nb, d + 1));
            }
        }
    }

    for (int i = 1; i <= N; i++) 
    {
        vis[i] = 0;
        if (df[a][i]) d1[i].pb(pii(df[a][i] * -1, a));
        if (df[a][i]) d2[a].pb(pii(df[a][i] * -1, i));
    }
}

struct E
{
    int dist, a, b, c, d;
};

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
    }

    for (int i = 1; i <= N; i++) BFS(i);

    for (int i = 1; i <= N; i++) 
    {
        sort(d1[i].begin(), d1[i].end());
        sort(d2[i].begin(), d2[i].end());
    }

    E ans = {0, 0, 0, 0, 0};
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) 
        if (df[i][j] && d1[i].size() && d2[j].size())
    {
        int a = 0;
        int b = 0;

        if (d1[i][a].SS == j) 
        {
            if (d1[i].size() == 1) continue;
            ++a;
        }
        if (d2[j][b].SS == i) 
        {
            if (d2[j].size() == 1) continue;
            ++b;
        }

        if (d1[i][a].SS == d2[j][b].SS)
        {
            if (d1[i].size() <= a + 1 && d2[j].size() <= b + 1) continue;

            if (d2[j].size() > b + 1 && 
                (d1[i].size() <= a + 1 || d1[i][a + 1].SS == j)) b++;

            else if (d1[i].size() > a + 1 &&
                (d2[j].size() <= b + 1 || d2[j][b + 1].SS == i)) a++;

            else if (d2[j].size() > b + 1 &&
                     d1[i][a + 1].FF >= d2[j][b + 1].FF) b++;
                     
            else a++;
        }

        // if (i == 2 && j == 4) cout << d1[i][a].SS << " " << d2[j][b].SS << endl;

        int dist = (df[i][j] * -1 + d1[i][a].FF + d2[j][b].FF) * -1;

        if (ans.dist < dist) ans = {dist, d1[i][a].SS, i, j, d2[j][b].SS};
    }

    cout << ans.a << " " << ans.b << " " << ans.c << " " << ans.d << endl;

    return 0;
} 