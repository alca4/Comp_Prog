/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
pii fourdir[4] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 1010;
char room[MAXN][MAXN];
int vis[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N = read(), M = read();
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> room[i][j];

    int cnt = 0;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) if (!vis[i][j] && room[i][j] == '.')
    {
        // cout << i << " " << j << endl;
        cnt++;
        queue<pii> pts;
        vis[i][j] = 1;
        pts.push({i, j});
        while (!pts.empty())
        {
            // cout << i << " " << j << endl;
            int a = pts.front().FF;
            int b = pts.front().SS;
            pts.pop();

            for (int i = 0; i < 4; i++)
            {
                int ta = fourdir[i].FF + a;
                int tb = fourdir[i].SS + b;
                if (1 <= ta && ta <= N &&
                    1 <= tb && tb <= M &&
                    !vis[ta][tb] &&
                    room[ta][tb] == '.')
                {
                    pts.push({ta, tb});
                    vis[ta][tb] = 1;
                }
            }
        }
    }

    cout << cnt << endl;
    return 0;
}