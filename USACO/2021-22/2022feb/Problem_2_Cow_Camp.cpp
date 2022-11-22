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

const int MAXN = 1010;
int T, K;
ld a, b;
ld e = 0.0;
int subs = 0;

ld p[MAXN][MAXN];

double advance(int n)
{
    return pow(a, n) * e + b * (1 - pow(a, n)) / (1 - a);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T >> K;
    T--;

    // e = T / 2.0;

    p[0][0] = 1.0;
    for (int i = 1; i <= T; i++) 
    {
        p[i][0] += p[i - 1][0] / 2.0;
        for (int j = 1; j <= T; j++) p[i][j] = (p[i - 1][j - 1] + p[i - 1][j]) / 2.0;
    }

    for (int j = 1; j <= T; j++)
    {
        a = b = 0.0;
        for (int i = 0; i <= T; i++) 
        {
            if (i <= floor(e)) a += p[T][i];
            else b += p[T][i] * i;
        }

        int lb = 0;
        int ub = K;

        int ans = 0;
        while (lb <= ub)
        {
            int mid = (lb + ub) / 2;

            if (floor(advance(mid)) == j - 1) ans = max(ans, mid);
            if (floor(advance(mid)) <= j - 1) lb = mid + 1;
            else ub = mid - 1;
        }

        ans++;
        if (ans > K - subs) ans = K - subs;

        e = advance(ans);
        subs += ans;
        if (subs == K) break;
    }

    cout << setprecision(12) << fixed << e + 1 << endl;
    return 0;
}