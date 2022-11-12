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

const int MAXN = 100010;
int N, K;
ll a[MAXN], b[MAXN];
ll c[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 1; i <= N; i++) cin >> b[i];
    
    for (int i = 1; i <= N; i++) c[i] = a[i] - b[i];
    sort(c + 1, c + 1 + N);

    ll cost = 0;
    int mid;
    if ((N - K) % 2 == 0) mid = (N - K) / 2;
    else mid = (N - K) / 2 + 1;

    for (int i = 1; i <= N - K; i++) cost += abs(c[mid] - c[i]);
    ll ans = cost;
    for (int i = 1; i <= K; i++)
    {

        cost += (mid - i + 1) * (c[mid + 1] - c[mid]);
        cost -= (N - K + i - mid) * (c[mid + 1] - c[mid]);

        cost -= c[mid] - c[i];
        mid++;
        cost += c[N - K + i] - c[mid];

        ans = min(ans, cost);
    }
    cout << ans << endl;
    return 0;
}