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
#define INF 1000000000000000000ll
#define MOD 1000000007ll
 
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 300010;
int N, M;
ll P, Q;
string grid[MAXN];
vector<ll> dist[MAXN];
vector<int> vis[MAXN];

pii slide[4] = {pii(0, 2), pii(2, 0), pii(-2, 0), pii(0, -2)};
int sreq[4] = {'L', 'U', 'D', 'R'};
pii rot[4] = {pii(1, 1), pii(-1, 1), pii(-1, -1), pii(1, -1)};
pair<char, char> rreq[4] = {{'D', 'R'}, {'U', 'R'}, {'U', 'L'}, {'D', 'L'}};

struct Point
{
  int x, y;
  ll dist;
};

bool operator<(const Point& p1, const Point& p2)
{
    return p1.dist < p2.dist;
}

int main()
{
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> N >> M >> P >> Q;
  for (int i = 0; i < N; i++) cin >> grid[i];
  for (int i = 0; i < N; i++) dist[i].resize(M);
  for (int i = 0; i < N; i++) vis[i].resize(M);

  priority_queue<Point> pq;

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++)
  {
    if (grid[i][j] == '.') 
    {
      pq.push({i, j, 0});
      dist[i][j] = 0;
    }
    else dist[i][j] = INF;
  }

  while (!pq.empty())
  {
    int x = pq.top().x;
    int y = pq.top().y;
    ll d = pq.top().dist * -1;
    pq.pop();

    if (vis[x][y]) continue;
    vis[x][y] = 1;

    for (int i = 0; i < 4; i++)
    {
      int dx = slide[i].FF;
      int dy = slide[i].SS;

      if (!(x + dx >= 0 && x + dx < N && y + dy >= 0 && y + dy < M)) continue;

      if (grid[x + dx / 2][y + dy / 2] == sreq[i]) 
      {
        if (dist[x + dx][y + dy] > dist[x][y] + Q)
        {
          dist[x + dx][y + dy] = dist[x][y] + Q;
          if (!vis[x + dx][y + dy])
            pq.push({x + dx, y + dy, -1 * dist[x + dx][y + dy]});
        }
      }
    }

    for (int i = 0; i < 4; i++)
    {
      int dx = rot[i].FF;
      int dy = rot[i].SS;

      if (!(x + dx >= 0 && x + dx < N && y + dy >= 0 && y + dy < M)) continue;

      if (grid[x + dx][y + dy] == rreq[i].FF || grid[x + dx][y + dy] == rreq[i].SS) 
      {
        if (dist[x + dx][y + dy] > dist[x][y] + P)
        {
          dist[x + dx][y + dy] = dist[x][y] + P;
          if (!vis[x + dx][y + dy])
            pq.push({x + dx, y + dy, -1 * dist[x + dx][y + dy]});
        }
      }
    }
  }

  ll ans = INF;
  for (int x = 0; x < N; x++) for (int y = 0; y < M; y++) for (int i = 0; i < 4; i++)
  {
    int dx = slide[i].FF;
    int dy = slide[i].SS;

    dx /= 2;
    dy /= 2;

    if (!(x + dx >= 0 && x + dx < N && y + dy >= 0 && y + dy < M)) continue;
    ans = min(ans, dist[x][y] + dist[x + dx][y + dy]);
  }

  if (ans == INF) cout << "-1" << endl;
  else cout << ans << endl;
  return 0;
}
