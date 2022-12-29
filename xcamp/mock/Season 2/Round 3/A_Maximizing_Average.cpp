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

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 300010;
int N, K;
ld arr[MAXN];
ld psum[MAXN];
ld ans = 0;

int test(ld v)
{
    for (int i = 1; i <= N; i++) arr[i] -= v;
    for (int i = 1; i <= N; i++) psum[i] = psum[i - 1] + arr[i];

    ld worst = 0;
    int ans = 0;
    for (int i = K; i <= N; i++)
    {
        if (psum[i] - worst >= 0) ans = 1;
        worst = min(worst, psum[i - K + 1]);
    }
    for (int i = 1; i <= N; i++) arr[i] += v;
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ld lb = 1;
    ld ub = 1000000;
    while (ub - lb >= 1e-6)
    {
        ld mid = (lb + ub) / 2;

        if (test(mid))
        {
            ans = max(ans, mid);
            lb = mid + 1e-6;
        }
        else
        {
            ub = mid - 1e-6;
        }
    }

    cout << setprecision(4) << fixed << ans << endl;
    return 0;
}