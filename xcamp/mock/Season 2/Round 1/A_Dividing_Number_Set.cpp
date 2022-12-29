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
#define INF 1e15
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

const int MAXN = 1000010;
int N;
ll arr[MAXN];
ld a1, a2;
ld avg1, avg2;
ll s1, s2;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    sort(arr + 1, arr + N + 1);

    for (int i = 1; i <= N; i++) 
    {
        avg2 += arr[i];
        s2 += arr[i];
    }
    avg2 /= N;

    for (int i = 1; i <= N; i++) a2 += (arr[i] - avg2) * (arr[i] - avg2);

    ld ans = a2;
    for (int i = 1; i < N; i++)
    {
        a1 += arr[i] * arr[i];

        a1 -= avg1 * avg1 * (i - 1);
        a1 -= avg1 * -2 * s1;
        avg1 *= (i - 1);
        avg1 += arr[i];
        avg1 /= i;
        s1 += arr[i];
        a1 += avg1 * -2 * s1;
        a1 += avg1 * avg1 * i;


        a2 -= arr[i] * arr[i];

        a2 -= avg2 * avg2 * (N - i + 1);
        a2 -= avg2 * -2 * s2;
        avg2 *= (N - i + 1);
        avg2 -= arr[i];
        avg2 /= (N - i);
        s2 -= arr[i];
        a2 += avg2 * -2 * s2;
        a2 += avg2 * avg2 * (N - i);
        
        // cout << a1 << " " << a2 << endl;
        ans = min(ans, a1 + a2);
    }
    cout << setprecision(9) << fixed << ans << endl;
    return 0;
}