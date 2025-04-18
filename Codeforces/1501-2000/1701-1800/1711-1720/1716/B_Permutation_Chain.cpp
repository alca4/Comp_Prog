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
#define MOD 1000000007
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

void solve()
{
    // cout << "===========" << endl;
    int N;
    cin >> N;
    
    cout << N << endl;
    int arr[MAXN];
    for (int i = 1; i <= N; i++) arr[i] = i;
    for (int i = 1; i <= N; i++) cout << arr[i] << " ";
    cout << endl;

    for (int j = 2; j <= N; j++)
    {
        swap(arr[j], arr[j - 1]);
        for (int i = 1; i <= N; i++) cout << arr[i] << " ";
        cout << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}