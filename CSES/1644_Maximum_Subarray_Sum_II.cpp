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

const int MAXN = 500010;
int N, A, B;
ll arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) arr[i] = arr[i - 1] + read();

    ll max_sum = -INF;
    multiset<ll> pos;
    for (int i = A; i <= N; i++)
    {
        pos.insert(arr[i - A]);
        if (i > B) pos.erase(pos.find(arr[i - B - 1]));
        max_sum = max(max_sum, arr[i] - *pos.begin());
    }

    cout << max_sum << endl;
    return 0;
}