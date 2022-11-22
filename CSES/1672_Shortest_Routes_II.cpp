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
#define INF 1000000000000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 510;
ll mat[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N, M, Q;
    cin >> N >> M >> Q;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) if (i != j) mat[i][j] = INF;
    for (int j = 1; j <= M; j++)
    {
        int a = read(), b = read();
        ll c = read();
        mat[a][b] = min(mat[a][b], c);
        mat[b][a] = min(mat[a][b], c);
    }

    for (int k = 1; k <= N; k++) for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);

    while (Q--)
    {
        int a = read(), b = read();
        if (mat[a][b] == INF) cout << -1 << endl;
        else cout << mat[a][b] << endl;
    }
    return 0;
}