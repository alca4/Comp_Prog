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
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 100010;
int N, M;
pii p[MAXN];
int c[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> p[i].FF >> p[i].SS;
    for (int i = 1; i <= N; i++) swap(p[i].FF, p[i].SS);
    for (int i = 1; i <= M; i++) cin >> c[i];

    sort(p + 1, p + 1 + N);
    sort(c + 1, c + 1 + M);

    int lb = 1, ub = min(N, M);
    int ans = 0;
    while (lb <= ub)
    {
        int mid = (lb + ub) / 2;

        int j = mid;
        for (int i = 1; i <= N; i++)
        {
            if (p[i].SS <= c[M - j + 1]) 
            {
                j--;
                if (j == 0) break;
            }
        }

        if (j == 0)
        {
            ans = mid;
            lb = mid + 1;
        }
        else ub = mid - 1;
    }

    cout << ans << endl;
    return 0;
}