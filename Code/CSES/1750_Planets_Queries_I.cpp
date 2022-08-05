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
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 500010;
int N, Q;
int nv[MAXN][35];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> nv[i][0];

    for (int i = 1; i < 35; i++) 
        for (int a = 1; a <= N; a++) nv[a][i] = nv[nv[a][i - 1]][i - 1];

    while (Q--)
    {
        int n = read(), j = read();
        int ans = n;
        while (j > 0)
        {
            int bit = log2(j & -j);
            ans = nv[ans][bit];
            j -= j & -j;
        }
        cout << ans << endl;
    }
    return 0;
}