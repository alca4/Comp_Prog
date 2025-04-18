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
ll INF = 1000000000;
ll MOD = 1000000007;

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

int N, M;
vector<vector<char>> lands;
vector<vector<int>> dist;
vector<vector<int>> val;
vector<vector<pii>> back;
vector<vector<int>> vis;
int dists[1000010];

int BFS(int a, int b)
{
    dist[a][b] = 1;
    int ans = 0;
    queue<pii> q;
    q.push({a, b});

    while (!q.empty())
    {
        int x = q.front().FF;
        int y = q.front().SS;
        q.pop();

        if (vis[x][y]) continue;
        vis[x][y] = 1;

        if (x == N - 1 && y == M - 1) 
        {
            ans = 1;
            break;
        }

        if (x < N - 1 && lands[x + 1][y] != '#') 
        {
            q.push({x + 1, y});
            back[x + 1][y].FF = 1;
            dist[x + 1][y] = dist[x][y] + 1;
        }
        if (y < M - 1 && lands[x][y + 1] != '#') 
        {
            q.push({x, y + 1});
            back[x][y + 1].SS = 1;
            dist[x][y + 1] = dist[x][y] + 1;
        }
    }

    if (ans == 0) return 0;
    val[N - 1][M - 1] = 1;

    for (int i = N - 1; i >= 0; i--) for (int j = M - 1; j >= 0; j--) 
    {
        if (val[i][j] && back[i][j].FF) val[i - 1][j] = 1;
        if (val[i][j] && back[i][j].SS) val[i][j - 1] = 1;
    }

    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)
        if (val[i][j]) dists[dist[i][j]]++;
    for (int i = 2; i < N + M - 1; i++) if (dists[i] == 1) return 1;
    return 2;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    lands.resize(N);
    vis.resize(N);
    dist.resize(N);
    back.resize(N);
    val.resize(N);
    for (int i = 0; i < N; i++) 
    {
        lands[i].resize(M);
        vis[i].resize(M);
        dist[i].resize(M);
        back[i].resize(M);
        val[i].resize(M);
        for (int j = 0; j < M; j++) cin >> lands[i][j];
    }

    cout << BFS(0, 0) << endl;
    return 0;
} 